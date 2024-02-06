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
        if(_state != nullptr)
            return;

        _state = std::make_unique<ChessBoardState>();
        ChessBoardState* state = GetState<ChessBoardState>();

        const int type[8] = {1, 2, 3, 4, 5, 3, 2, 1};
        for(int k = 0; k < 2; ++k)
        {
            for(int c = 0; c< 8; ++c)
            {
                // Spawn pawn
                auto p1 = std::make_shared<ChessObject>(
                    Pos(c, 1 + !k * 5),
                    PieceType::PAWN,
                    static_cast<PieceColor>(k)
                );                
                state->square[1 + !k * 5][c].piece = p1;
                state->pieces.push_back(p1);
                // Spawn other pieces 
                auto p2 = std::make_shared<ChessObject>(
                    Pos(c, 0 + !k * 7),
                    static_cast<PieceType>(type[c]),
                    static_cast<PieceColor>(k)
                );
                state->square[0 + !k * 7][c].piece = p2;
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

    bool ChessBoard::ApplyAction(Action& action)
    {
        ChessBoardState* state = GetState<ChessBoardState>();
        auto cAction = reinterpret_cast<ChessAction&>(action);
        
        switch(cAction.type)
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

            if(state->selectedObj->m_Color != state->currentColor)
            {
                state->selectedObj = nullptr;
                break;
            }

            // Highlight the board;
            for (auto& move : state->selectedObj->m_AvailableMove)
            {
                Pos pos = move.pos;

                // If 'check', move must make the 'check'
                if(state->isCheck[PieceColorToInt(state->selectedObj->m_Color)] && 
                   !(state->posToDefCheck.contains(pos)))
                   continue;

                state->square[pos.y][pos.x].boardSelected = true;
            }

            return true;
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
                    if(state->isCheck[PieceColorToInt(state->selectedObj->m_Color)] && 
                       !(state->posToDefCheck.contains(pos)))
                        continue;

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
            ChangeColor();

            if(IsCheckmate())
            {
                std::cout << "Checkmate!, " << static_cast<int>(state->currentColor) << " lose\n";
            }
            return true;
        }
        }
        return false;
    }

    void ChessBoard::Move(ChessObjectRef &piece, Pos dst)
    {
        ChessBoardState* state = GetState<ChessBoardState>();

        Pos src = piece->m_Pos;
        Pos dstPiecePos = dst;
        
        // If en passant, real piece position is diffirent
        if(piece->m_PieceType == PieceType::PAWN && 
           dst == state->lastEnPassantPos)
        {
            dstPiecePos.y = src.y;
        }
        // Reset en passant
        state->lastEnPassantPos = {-1, -1};

        int srcIdx = static_cast<int>(piece->m_Color);

        if(state->square[dstPiecePos.y][dstPiecePos.x].piece != nullptr)
        {
            // captured piece
            // TODO: need optimization
            for(auto it = state->pieces.begin(); it != state->pieces.end(); it++)
            {
                if((*it)->m_Pos == dstPiecePos)
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
            // Move Rook
            int dir = dst.x - piece->m_Pos.x < 0? -1: 1;            
            auto rook = state->square[piece->m_Pos.y][dir==-1? 0 : 7].piece;

            Move(rook, dst - Pos{dir, 0});
        }

        else if(piece->m_PieceType == PieceType::PAWN)
        {
            // TODO: Add Promotion

            // En passant
            if(piece->m_Moved == false)
            {
                int dir = piece->m_Color == PieceColor::BLACK? -1: 1;
                state->lastEnPassantPos.x = dst.x;
                state->lastEnPassantPos.y = dst.y - dir;
            }
        }   
        piece->m_Moved = true;    

    }

    void ChessBoard::UpdateBoardState()
    {
        ChessBoardState* state = GetState<ChessBoardState>();
        std::set<Pos> kingsAvailablePos[2];

        // Reset settings
        state->posToDefCheck.clear();
        for(int i = 0; i < 2; ++i)
        {
            state->isCheck[i] = false;
        }        

        // Remove previous available position
        // And reset other states.
        for(auto& piece : state->pieces)
        {
            piece->m_AvailableMove.clear();
            piece->m_CanMove = true;
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
            // Checking for castling
            for(int x = -2; x <= 2; x += 4)
            {
                Pos curPos = state->kings[i]->m_Pos + Pos{x, 0};
                if(IsInsideTheBoard(curPos))
                {
                    kingsAvailablePos[i].insert(curPos);
                }
            }
        }

        // Update all piece's available positions;
        for(auto& piece : state->pieces)
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
    }

    /**
     * @param pos position for add
     * @param piece current piece
     * @param cond condition for destination position 'pos'
     * @param stPos if check, start index of m_AvailableMove for adding state->posToDefCheck
    */
    bool ChessBoard::AddAvailablePosition(Pos pos, ChessObjectRef& piece, MoveCondition cond, int stPosIdx,
                                          std::set<Pos>* kingsAvailablePos, ChessBoardState* state)
    {          
        if(!IsInsideTheBoard(pos))
            return false;

        bool deleteKingsPos = false;
        if(kingsAvailablePos != nullptr)
        {
            // Other player index
            int idx = (static_cast<int>(piece->m_Color) + 1) % 2;
            if (pos == state->kings[idx]->m_Pos)
            {
                state->isCheck[idx] = true;

                // Add position for defense the 'check'
                if(stPosIdx != -1)
                {
                    for(int i = stPosIdx; i < piece->m_AvailableMove.size(); ++i)
                    {
                        state->posToDefCheck.insert(piece->m_AvailableMove[i].pos);
                    }
                }
                state->posToDefCheck.insert(piece->m_Pos);
            }

            auto iter = kingsAvailablePos->find(pos);
            if(iter != kingsAvailablePos->end())
            {
                kingsAvailablePos->erase(iter);
                deleteKingsPos = true;
            }
        }
        
        auto dst = state->square[pos.y][pos.x].piece;
        // When the state before is true, 
        // and if i will use this state(cond & ~~~), return true
        bool emptyCond = dst == nullptr && (cond & MOVE_TO_EMPTY);
        bool enemyCond = dst != nullptr && dst->m_Color != piece->m_Color && (cond & MOVE_TO_ENEMY);

        // If both condition is false, return false
        // Is not empty and is not enemy
        if(!emptyCond && !enemyCond)
            return false;

        piece->m_AvailableMove.emplace_back(Pos{pos.x, pos.y}, Movement::State::NORMAL);

        return true;
    }

    void ChessBoard::UpdateAvailablePosition(ChessObjectRef& piece, std::set<Pos>& kingsAvailablePos)
    {
        ChessBoardState* state = GetState<ChessBoardState>();

        if(!piece->m_CanMove)
            return;

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
            // other king's position
            Pos kingPos = state->kings[!PieceColorToInt(piece->m_Color)]->m_Pos;
            for(int i = 0; i < move.size(); ++i)
            {
                Pos curPos = piece->m_Pos;
                bool canAdd = true;

                // Start index of positions in the current direction
                int dirStIdx = piece->m_AvailableMove.size();

                Pos tmp = piece->m_Pos;
                bool isOnly = true;
                while(true)
                {
                    curPos += move[i];

                    if(!IsInsideTheBoard(curPos))
                        break;

                    auto dst = state->square[curPos.y][curPos.x].piece;
                    if(canAdd)
                    {
                        canAdd = AddAvailablePosition(curPos, piece, MOVE_TO_EMPTY | MOVE_TO_ENEMY, dirStIdx,
                                                      &kingsAvailablePos, state);
                        if(dst != nullptr)
                            canAdd = false;              
                    }

                    // The condition of dst piece that makes the 'check' must be 
                    // the only piece between the kings and the enemy.
                    if(dst != nullptr && kingPos != curPos)
                    {
                        if(Pos::OnLine(piece->m_Pos, dst->m_Pos, kingPos))
                        {
                            if(tmp == piece->m_Pos)
                            {
                                tmp = curPos;
                            }
                            else
                            {
                                isOnly = false;
                            }
                        }
                    }                    
                }

                if(tmp != piece->m_Pos && isOnly)
                {
                    auto dst = state->square[tmp.y][tmp.x].piece;
                    // the current dst pos is a pos to prevent checking
                    // so do not move
                    dst->m_AvailableMove.clear();
                    dst->m_CanMove = false;
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
                
                int dir = piece->m_Color == PieceColor::BLACK? -1: 1;
                for(int i = 0; i < 4; ++i)
                    move[i].y *= dir;

                // normal 1 step move
                p = piece->m_Pos + move[0];
                AddAvailablePosition(p, piece, MOVE_TO_EMPTY, -1, &kingsAvailablePos, state);

                // normal 2 step move
                if(!piece->m_Moved && state->square[p.y][p.x].piece == nullptr)
                {            
                    p = piece->m_Pos + move[1];    
                    AddAvailablePosition(p, piece, MOVE_TO_EMPTY, -1, &kingsAvailablePos, state);
                }
                
                for(int i = 2; i < 4; ++i)
                {
                    Pos p = piece->m_Pos + move[i];
                    
                    
                    auto moveState = MOVE_TO_ENEMY;
                    // En passant condition
                    if(state->lastEnPassantPos == p)
                        moveState |= MOVE_TO_EMPTY;

                    AddAvailablePosition(p, piece, moveState, -1,
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
                    AddAvailablePosition(curPos, piece, MOVE_TO_EMPTY | MOVE_TO_ENEMY, -1,
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
                    // TODO: Add castling
                    if(abs(p.x - piece->m_Pos.x) == 2)
                    {
                        if(!piece->m_Moved && !state->isCheck[static_cast<int>(piece->m_Color)])
                        {
                            Pos tmp;
                            int dir = p.x - piece->m_Pos.x < 0? -1: 1;

                            // The king does not pass through or finish on a square 
                            // that is attacked by an enemy piece.
                            tmp = p - Pos{dir, 0};
                            if (!kingsAvailablePos.contains(tmp))
                            {
                                continue;
                            }

                            // Exist Rook
                            auto& rook = state->square[piece->m_Pos.y][dir==-1? 0 : 7].piece;
                            // if moved, this is not rook
                            if(rook == nullptr || rook->m_Moved)
                                continue;
                            
                            bool able = true;
                            tmp = piece->m_Pos;
                            tmp.x += dir;
                            while(able && IsInsideTheBoard(tmp) && 0 < tmp.x && tmp.x < 7)
                            {
                                able = state->square[tmp.y][tmp.x].piece == nullptr;
                                tmp.x += dir;                                
                            }

                            if(able)
                            {
                                AddAvailablePosition(p, piece, MOVE_TO_EMPTY, -1, nullptr, state);
                            }
                        }
                    }
                    else
                    {

                        AddAvailablePosition(p, piece, MOVE_TO_EMPTY | MOVE_TO_ENEMY, -1,
                                             nullptr, state);
                    }
                }
            }
            #pragma endregion
        
        }
    }

    bool ChessBoard::IsCheckmate()
    {
        ChessBoardState* state = GetState<ChessBoardState>();
        int color = PieceColorToInt(state->currentColor);

        if(state->isCheck[color])
        {
            int availableMoveCnt = state->kings[color]->m_AvailableMove.size();
            if(availableMoveCnt == 0)
            {                
                for(auto& piece : state->pieces)
                {
                    if(piece->m_Color != state->currentColor)
                        continue;
                    for(auto& move :piece->m_AvailableMove)
                    {
                        if(state->posToDefCheck.contains(move.pos))
                        {
                            availableMoveCnt++;
                            return false;
                        }
                    }               
                }
            }
            else 
            {
                return false;
            }
            return true;
        }
        return false;
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

    void ChessBoard::ChangeColor()
    {
        ChessBoardState* state = GetState<ChessBoardState>();

        int color = (PieceColorToInt(state->currentColor) + 1) % 2;
        state->currentColor = IntToPieceColor(color);
    }

} // namespace DawnBoard::Chess
