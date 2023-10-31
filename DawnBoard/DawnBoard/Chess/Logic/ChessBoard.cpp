#include "ChessBoard.hpp"


#include <DawnBoard/Chess/Object/ChessObject.hpp>
#include <DawnBoard/Chess/Logic/ChessBoardState.hpp>
#include <DawnBoard/Chess/Logic/ChessAction.hpp>

#include <memory>
#include <iostream>

namespace DawnBoard::Chess
{

    void ChessBoard::Init()
    {
        if(m_State != nullptr)
            return;

        m_State = std::make_unique<ChessBoardState>();
        ChessBoardState* state = GetState<ChessBoardState>();

        const int type[8] = {1, 2, 3, 4, 5, 3, 2, 1};
        for(int k = 0; k < 2; ++k)
        {
            for(int c = 0; c< 8; ++c)
            {
                // Spawn pawn
                auto p1 = std::make_shared<ChessObject>(
                    Pos(1 + k * 5, c),
                    PieceType::PAWN,
                    static_cast<PieceColor>(k)
                );                
                state->square[1 + k * 5][c] = p1;
                state->pieces.push_back(p1);
                // Spawn other pieces 
                auto p2 = std::make_shared<ChessObject>(
                    Pos(0 + k * 7, c),
                    static_cast<PieceType>(type[c]),
                    static_cast<PieceColor>(k)
                );
                state->square[0 + k * 7][c] = p2;
                state->pieces.push_back(p2);
            }        

        }

        state->progress = FieldProgress::READY;
    }

    void ChessBoard::Start()
    {
        ChessBoardState* state = GetState<ChessBoardState>();

        state->progress = FieldProgress::RUNNING;
    }

    void ChessBoard::Clear()
    {
        ChessBoardState* state = GetState<ChessBoardState>();

        for(int r = 0; r < 8; ++r)
            for(int c = 0; c < 8; ++c)
                state->square[r][c] = nullptr;

        
        Init();
    }

    void ChessBoard::ApplyAction(Action& action)
    {
        
        switch(reinterpret_cast<ChessAction&>(action).type)
        {
        case ActionType::SELECT:
        {
            auto& act = reinterpret_cast<SelectAction&>(action);    
            m_PossiblePos = GetPossiblePosition(act.pos);

            break;
        }

        case ActionType::MOVE:
        {
            auto& act = reinterpret_cast<MoveAction&>(action); 

            break;
        }
        }
    }

    std::vector<Pos> ChessBoard::GetPossiblePosition(Pos pos)
    {
        ChessBoardState* state = GetState<ChessBoardState>();
        
        std::vector<Pos> possiblePos;
        std::shared_ptr<ChessObject> target = state->square[pos.x][pos.y];

        if (target == nullptr)
            return possiblePos;

        switch(target->m_PieceType)
        {
        case PieceType::PAWN:
        {
            Pos move[] = {
                {1, 0}, {2, 0}, {2, 1}, {2, -1}
            };
            
            uint8_t dir = target->m_Color == PieceColor::BLACK? 1: -1;
            for(int i = 0; i < 4; ++i)
                move[i].x *= dir;

            if(IsAvailablePos(pos + move[0]))
            {
                possiblePos.push_back(pos + move[0]);
            }

            // if(!target->m_Moved)
            // {                
            //     if(IsAvailablePos(pos + move[1]))
            //     {
            //         possiblePos.push_back(pos + move[1]);
            //     }
            // }
            
            for(int i = 2; i < 4; ++i)
            {
                Pos p = pos + move[i];
                if(!IsAvailablePos(p))
                {
                    continue;
                }

                if (state->square[p.x][p.y] != nullptr && 
                    state->square[p.x][p.y]->m_Color != target->m_Color)
                {
                    possiblePos.push_back(p);
                }
            }
            

            break;
        }
        #pragma region Sliding movement

        case PieceType::ROOK:
        {
            const Pos move[] = {
                {1, 0}, {0, 1}, {-1, 0}, {0, -1}
            };

            for(int i = 0; i < 4; ++i)
            {
                Pos curPos = pos;
                while(true)
                {
                    curPos += move[i];
                    
                    if (!IsAvailablePos(curPos))
                        break;

                    possiblePos.emplace_back(curPos.x, curPos.y);
                }
            }
            
            break;
        }
        case PieceType::BISHOP:
        {
            const Pos move[] = {
                {1, 1}, {-1, 1}, {-1, -1}, {1, -1}
            };

            for(int i = 0; i < 4; ++i)
            {
                Pos curPos = pos;
                while(true)
                {
                    curPos += move[i];
                    
                    if (!IsAvailablePos(curPos))
                        break;

                    possiblePos.emplace_back(curPos.x, curPos.y);
                }
            }

            break;
        }
        case PieceType::QUEEN:
        {
            const Pos move[] = {
                {1, 0}, {0, 1}, {-1, 0}, {0, -1},
                {1, 1}, {-1, 1}, {-1, -1}, {1, -1}
            };

            for(int i = 0; i < 8; ++i)
            {
                Pos curPos = pos;
                while(true)
                {
                    curPos += move[i];
                    
                    if (!IsAvailablePos(curPos))
                        break;

                    possiblePos.emplace_back(curPos.x, curPos.y);
                }
            }

            break;
        }
        #pragma endregion

        #pragma region Single movement
        case PieceType::KING:
        {

            const Pos move[] = {
                {1, 0}, {0, 1}, {-1, 0}, {0, -1},
                {1, 1}, {-1, 1}, {-1, -1}, {1, -1}
            };
            for(int i = 0; i < 8; ++i)
            {
                Pos curPos = pos + move[i];
                if (IsAvailablePos(curPos))
                    possiblePos.emplace_back(curPos.x, curPos.y);
            }

            // TODO: Add castling
            // if (!target->m_Moved)
            // {

            // }

            break;
        }
        case PieceType::KNIGHT:
        {
            const Pos move[] = {
                {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                {1, 2}, {-1, 2}, {1, -2}, {-1, -2}
            };
            for(int i = 0; i < 8; ++i)
            {
                Pos curPos = pos + move[i];
                if (IsAvailablePos(curPos))
                    possiblePos.emplace_back(curPos.x, curPos.y);
            }

            break;
        }
        #pragma endregion
        
        default:
            break;
        }

        return possiblePos;
    }

    bool ChessBoard::IsAvailablePos(Pos pos)
    {
        // Check pos that enemy stayed or empty

        return pos.x >= 0 && pos.y >= 0 && pos.x < 8 && pos.y < 8;
    }

    int ChessBoard::GetPieceCount()
    {
        ChessBoardState* state = GetState<ChessBoardState>();

        int cnt = 0;
        for(int i = 0; i < 8; ++i)
        {
            for(int j = 0; j < 8; ++j)
            {
                if(state->square[i][j] != nullptr)
                {
                    cnt++;
                }
            }
        }

        return cnt;
    }

} // namespace DawnBoard::Chess
