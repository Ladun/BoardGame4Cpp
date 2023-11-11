#include "ChessBoard.hpp"

#include <DawnBoard/Chess/Object/ChessObject.hpp>
#include <DawnBoard/Chess/Logic/ChessAction.hpp>

#include <memory>
#include <set>
#include <iostream>
#include <functional>

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
                    Pos(c, 1 + k * 5),
                    PieceType::PAWN,
                    static_cast<PieceColor>(k)
                );                
                state->square[1 + k * 5][c].piece = p1;
                state->pieces.push_back(p1);
                // Spawn other pieces 
                auto p2 = std::make_shared<ChessObject>(
                    Pos(c, 0 + k * 7),
                    static_cast<PieceType>(type[c]),
                    static_cast<PieceColor>(k)
                );
                state->square[0 + k * 7][c].piece = p2;
                state->pieces.push_back(p2);
                // King stores in other array
                if(type[c] == 5)
                {
                    state->kings[k] = p2;
                }
            }        

        }

        UpdateBoardState();

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
                state->square[r][c].piece = nullptr;

        
        Init();
    }

    void ChessBoard::ApplyAction(Action& action)
    {
        ChessBoardState* state = GetState<ChessBoardState>();
        
        switch(reinterpret_cast<ChessAction&>(action).type)
        {
        case ActionType::SELECT:
        {
            auto& act = reinterpret_cast<SelectAction&>(action);   

            if(state->selectedObj != nullptr)
            {
                // Reset board highlight
                for (auto& pos : state->selectedObj->m_AvailablePos)
                {
                    state->square[pos.y][pos.x].boardSelected = false;
                }
                
                // If select same position, just release the selected object
                auto prevPos = state->selectedObj->m_Pos;

                state->selectedObj = nullptr;
                if(prevPos == act.pos)
                {
                    break;
                }
            }

            state->selectedObj = state->square[act.pos.y][act.pos.x].piece;
            if(state->selectedObj == nullptr)
                break;

            // Highlight the board;
            for (auto& pos : state->selectedObj->m_AvailablePos)
            {
                state->square[pos.y][pos.x].boardSelected = true;
            }
            break;
        }

        case ActionType::MOVE:
        {
            auto& act = reinterpret_cast<MoveAction&>(action); 
            if(state->selectedObj == nullptr)
                break;

            break;
        }
        }
    }

    void ChessBoard::UpdateBoardState()
    {
        ChessBoardState* state = GetState<ChessBoardState>();
        std::set<Pos> kingsAvailablePos[2];

        // Calculate initial king's available position to check 'checkmate' and 'check'.
        // So it includes king's current position
        for(int i = 0; i < 2; ++i)
        {
            // Get positions;
            for(int x = -1; x <= 1; ++x)
            {
                for(int y = -1; y <= 1; ++y)
                {
                    Pos curPos = state->kings[i]->m_Pos + Pos{x, y};
                    if(IsInsideTheBoard(curPos))
                    {
                        kingsAvailablePos[i].insert(curPos);
                    }
                }
            }
        }

        // Update all piece's available positions;
        for(auto piece : state->pieces)
        {
            if(piece->m_PieceType != PieceType::KING)
                UpdateAvailablePosition(piece, kingsAvailablePos[static_cast<int>(piece->m_Color)]);
        }

        // Update king's movement
        for(int i = 0; i < 2; ++i)
        {
            // Remove current position, 
            // because current 'kingsAvailablePos' is position that kings can move
            auto iter = kingsAvailablePos[i].find(state->kings[i]->m_Pos);
            if(iter != kingsAvailablePos[i].end())
            {
                kingsAvailablePos[i].erase(iter);
            }
            else
            {
                // TODO: Add "check" state
            }

            for(auto p : kingsAvailablePos[i])
            {   
                auto dst = state->square[p.y][p.x].piece;
                if(dst == nullptr || (dst != nullptr && dst->m_Color != state->kings[i]->m_Color))
                    state->kings[i]->m_AvailablePos.push_back(p);
            }

            // TODO: Add castling
        }
    }

    void ChessBoard::UpdateAvailablePosition(ChessObjectRef& piece, std::set<Pos>& kingsAvailablePos)
    {
        ChessBoardState* state = GetState<ChessBoardState>();
        std::function<void(Pos)> pushFunc = [&](Pos p) {

            auto iter = kingsAvailablePos.find(p);
            if(iter != kingsAvailablePos.end())
            {
                kingsAvailablePos.erase(iter);
            }
            piece->m_AvailablePos.emplace_back(p.x, p.y);
        };

        // Remove previous available position
        piece->m_AvailablePos.clear();

        // Checking movement type
        bool isSlidingMovement = (piece->m_PieceType == PieceType::ROOK ||
                                  piece->m_PieceType == PieceType::QUEEN ||
                                  piece->m_PieceType == PieceType::BISHOP);
        
        // Assign available position of current piece
        if(isSlidingMovement)
        {
            std::vector<Pos> move;
            // Set movement direction
            if(piece->m_PieceType == PieceType::ROOK || piece->m_PieceType == PieceType::QUEEN)
            {
                move.insert(move.end(), {{1, 0}, {0, 1}, {-1, 0}, {0, -1}});
            }

            if(piece->m_PieceType == PieceType::BISHOP || piece->m_PieceType == PieceType::QUEEN)
            {
                move.insert(move.end(), {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}});
            }

            // Make movement
            for(int i = 0; i < move.size(); ++i)
            {
                Pos curPos = piece->m_Pos;
                while(true)
                {
                    curPos += move[i];
                    
                    if (!IsInsideTheBoard(curPos) || 
                        state->square[curPos.y][curPos.x].piece != nullptr)
                        break;

                    // There must be an opponent or nothing in the position to move
                    auto dst = state->square[curPos.y][curPos.x].piece;
                    if(dst == nullptr || (dst != nullptr && dst->m_Color != piece->m_Color))
                        pushFunc(curPos);
                }
            }
        }
        else
        {                
            #pragma region Single movement
            if(piece->m_PieceType == PieceType::PAWN)
            {
                Pos move[] = {
                    {0, 1}, {0, 2}, {1, 2}, {-1, 2} , {1, 1}, {-1, 1}
                };
                Pos p{0, 0};
                
                uint8_t dir = piece->m_Color == PieceColor::BLACK? 1: -1;
                for(int i = 0; i < 6; ++i)
                    move[i].y *= dir;

                // normal 1 step move
                p = piece->m_Pos + move[0];
                if(IsInsideTheBoard(p) && 
                   state->square[p.y][p.x].piece == nullptr)
                {
                    pushFunc(p);
                }

                // normal 1 move
                if(!piece->m_Moved)
                {            
                    p = piece->m_Pos + move[1];    
                    if(IsInsideTheBoard(p) && 
                       state->square[p.y][p.x].piece == nullptr)
                    {
                        pushFunc(p);  
                    }
                }
                
                for(int i = 2; i < 6; ++i)
                {
                    Pos p = piece->m_Pos + move[i];
                    if(!IsInsideTheBoard(p))
                        continue;
                    
                    // En passant condition
                    if(i >= 4 && state->lastPawnPos != p)
                        continue;

                    if (state->square[p.y][p.x].piece != nullptr && 
                        state->square[p.y][p.x].piece->m_Color != piece->m_Color)
                    {
                        pushFunc(p);  
                    }
                }
            }
            else if(piece->m_PieceType == PieceType::KNIGHT)
            {
                const Pos move[] = {
                    {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                    {1, 2}, {-1, 2}, {1, -2}, {-1, -2}
                };
                for(int i = 0; i < 8; ++i)
                {
                    Pos curPos = piece->m_Pos + move[i];
                    if (!IsInsideTheBoard(curPos))
                        continue;

                    auto dst = state->square[curPos.y][curPos.x].piece;
                    if(dst == nullptr || (dst != nullptr && dst->m_Color != piece->m_Color))
                        pushFunc(curPos);  
                }
            }
            #pragma endregion
        
        }
    }

    bool ChessBoard::IsInsideTheBoard(Pos pos)
    {
        // Check pos that enemy stayed or empty

        return pos.x >= 0 && pos.y >= 0 && pos.x < 8 && pos.y < 8;
    }

    int ChessBoard::GetPieceCount()
    {
        ChessBoardState* state = GetState<ChessBoardState>();

        return state->pieces.size();
    }

} // namespace DawnBoard::Chess
