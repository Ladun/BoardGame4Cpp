#include "ChessBoard.hpp"

#include <DawnBoard/Chess/ChessObject.hpp>
#include <DawnBoard/Chess/ChessAction.hpp>

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
                for (auto& move : state->selectedObj->m_AvailableMove)
                {
                    Pos pos = move.pos;
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
            for (auto& move : state->selectedObj->m_AvailableMove)
            {
                Pos pos = move.pos;

                // If 'check', move must make the 'check'
                auto& tar = state->square[pos.y][pos.x].piece;
                if(state->isCheck[ColorToInt(state->selectedObj->m_Color)] && 
                   !(tar != nullptr && tar->m_MakeCheck))
                   continue;

                state->square[pos.y][pos.x].boardSelected = true;
            }

            state->needRender = true;
            break;
        }

        case ActionType::MOVE:
        {
            auto& act = reinterpret_cast<MoveAction&>(action); 
            if(state->selectedObj == nullptr)
                break;

            bool movable = false;
            for (auto& move : state->selectedObj->m_AvailableMove)
            {
                Pos pos = move.pos;
                if(pos == act.dst)
                {
                    movable = true;
                    break;
                }                
            }
            if(!movable)
                break;

            Move(state->selectedObj, act.dst);
            // Reset board highlight
            for (auto& move : state->selectedObj->m_AvailableMove)
            {
                Pos pos = move.pos;
                state->square[pos.y][pos.x].boardSelected = false;
            }
            state->selectedObj = nullptr;
            UpdateBoardState();

            state->needRender = true;
            break;
        }
        }
    }

    void ChessBoard::Move(ChessObjectRef &piece, Pos dst)
    {
        ChessBoardState* state = GetState<ChessBoardState>();

        Pos src = piece->m_Pos;
        int srcIdx = static_cast<int>(piece->m_Color);
        piece->m_Moved = true;

        if(state->square[dst.y][dst.x].piece != nullptr)
        {
            // captured piece
            // TODO: need optimization
            for(auto it = state->pieces.begin(); it != state->pieces.end(); it++)
            {
                if((*it)->m_Pos == dst)
                {
                    (*it)->m_Captured = true;
                    state->pieces.erase(it);
                    break;
                }
            }
        }

        // Apply move on board
        state->square[dst.y][dst.x].piece = state->square[src.y][src.x].piece;
        state->square[src.y][src.x].piece = nullptr;

        // Update position
        state->square[dst.y][dst.x].piece->m_Pos = dst;

        if(piece->m_PieceType == PieceType::KING)
        {
            // TODO: Add castling logics
        }

        else if(piece->m_PieceType == PieceType::PAWN)
        {
            // TODO: Add Promotion
        }       

    }

    void ChessBoard::UpdateBoardState()
    {
        ChessBoardState* state = GetState<ChessBoardState>();
        std::set<Pos> kingsAvailablePos[2];

        for(int i = 0; i < 2; ++i)
        {
            state->isCheck[i] = false;
        }

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
            {
                int otherIdx = (static_cast<int>(piece->m_Color) + 1) % 2;
                UpdateAvailablePosition(piece, kingsAvailablePos[otherIdx]);
            }
        }

        // Update king's movement
        for(int i = 0; i < 2; ++i)
        {
            UpdateAvailablePosition(state->kings[i], kingsAvailablePos[i]);
        }

        // TODO: Check the checkmate
        int color = (ColorToInt(state->currentColor) + 1) % 2;
        state->currentColor = IntToColor(color);
        if(state->isCheck[color])
        {
            int availableMoveCnt = state->kings[color]->m_AvailableMove.size();
            if(availableMoveCnt > 0)
            {
                // No problem
            }
            else
            {
                
                for(auto piece : state->pieces)
                {
                    if(piece->m_Color != state->currentColor)
                        continue;
                    
                }
            }
        }
    }

    bool ChessBoard::AddAvailablePosition(Pos pos, ChessObjectRef& piece, MoveCondition cond,
                                          std::set<Pos>* kingsAvailablePos, ChessBoardState* state)
    {          
        if(!IsInsideTheBoard(pos))
            return false;
        
        auto dst = state->square[pos.y][pos.x].piece;
        // When the state before is true, 
        // and if i will use this state(cond & ~~~), return true
        bool emptyCond = dst == nullptr && (cond & MOVE_TO_EMPTY);
        bool enemyCond = dst != nullptr && dst->m_Color != piece->m_Color && (cond & MOVE_TO_ENEMY);

        // If both condition is false, return false
        // Is not empty and is not enemy
        if(!emptyCond && !enemyCond)
            return false;
        Movement::State moveState = Movement::State::NORMAL;

        if(kingsAvailablePos != nullptr)
        {
            // Other player index
            int idx = (static_cast<int>(piece->m_Color) + 1) % 2;
            if (pos == state->kings[idx]->m_Pos)
            {
                state->isCheck[idx] = true;
                piece->m_MakeCheck = true;
            }

            auto iter = kingsAvailablePos->find(pos);
            if(iter != kingsAvailablePos->end())
            {
                kingsAvailablePos->erase(iter);
            }
        }
        piece->m_AvailableMove.emplace_back(Pos{pos.x, pos.y}, Movement::State::NORMAL);

        return true;
    }

    void ChessBoard::UpdateAvailablePosition(ChessObjectRef& piece, std::set<Pos>& kingsAvailablePos)
    {
        ChessBoardState* state = GetState<ChessBoardState>();

        // Remove previous available position
        // And reset other states.
        piece->m_AvailableMove.clear();
        piece->m_MakeCheck = false;

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

                    bool isAdd = AddAvailablePosition(curPos, piece, MOVE_TO_EMPTY | MOVE_TO_ENEMY,
                                                      &kingsAvailablePos, state);

                    if(!isAdd || state->square[curPos.y][curPos.x].piece != nullptr) 
                        break;
                }
            }
        }
        else
        {                
            #pragma region Single movement
            if(piece->m_PieceType == PieceType::PAWN)
            {
                Pos move[] = {
                    {0, 1}, {0, 2}, {1, 1}, {-1, 1}
                };
                Pos p{0, 0};
                
                uint8_t dir = piece->m_Color == PieceColor::BLACK? 1: -1;
                for(int i = 0; i < 6; ++i)
                    move[i].y *= dir;

                // normal 1 step move
                p = piece->m_Pos + move[0];
                AddAvailablePosition(p, piece, MOVE_TO_EMPTY, &kingsAvailablePos, state);

                // normal 2 step move
                if(!piece->m_Moved)
                {            
                    p = piece->m_Pos + move[1];    
                    AddAvailablePosition(p, piece, MOVE_TO_EMPTY, &kingsAvailablePos, state);
                }
                
                for(int i = 2; i < 4; ++i)
                {
                    Pos p = piece->m_Pos + move[i];
                    
                    
                    auto moveState = MOVE_TO_ENEMY;
                    // En passant condition
                    if(state->lastEnPassantPos == p)
                        moveState |= MOVE_TO_EMPTY;

                    AddAvailablePosition(p, piece, MOVE_TO_ENEMY,
                                         &kingsAvailablePos, state);
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
                    AddAvailablePosition(curPos, piece, MOVE_TO_EMPTY | MOVE_TO_ENEMY,
                                         &kingsAvailablePos, state);
                }
            }
            else if(piece->m_PieceType == PieceType::KING)
            {                
                // Remove current position, 
                // because current 'kingsAvailablePos' is position that kings can move
                auto iter = kingsAvailablePos.find(piece->m_Pos);
                if(iter != kingsAvailablePos.end())
                {
                    kingsAvailablePos.erase(iter);
                }

                for(auto p : kingsAvailablePos)
                {   
                    AddAvailablePosition(p, piece, MOVE_TO_EMPTY | MOVE_TO_ENEMY,
                                         nullptr, state);
                }

                if(!piece->m_Moved && !state->isCheck[static_cast<int>(piece->m_Color)])
                {
                    // TODO: Add castling

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
