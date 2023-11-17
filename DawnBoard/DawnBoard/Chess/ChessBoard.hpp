#pragma once

#include <vector>

#include <DawnBoard/Base/Field.hpp>
#include <DawnBoard/Chess/ChessObject.hpp>
#include <DawnBoard/Chess/ChessBoardState.hpp>
#include <DawnBoard/Chess/Utils.hpp>

namespace DawnBoard::Chess
{
    // About movement
    using MoveCondition = uint8_t;
    const MoveCondition MOVE_TO_EMPTY = 1;
    const MoveCondition MOVE_TO_ENEMY = 2;

    class ChessBoard : public Field
    {
    public:
        virtual void Init();
        virtual void Start();
        virtual void Clear();

        virtual bool ApplyAction(Action& action);

        int GetPieceCount();

    private:
        void ChangeColor();

        // Movement
        void Move(ChessObjectRef& piece, Pos dst);
        
        // Movement creation
        void UpdateBoardState();
        bool AddAvailablePosition(Pos pos, ChessObjectRef& piece, MoveCondition cond, int stPosIdx,
                                  std::set<Pos>* kingsAvailablePos, ChessBoardState* state);
        void UpdateAvailablePosition(ChessObjectRef& piece, std::set<Pos>& kingsAvailablePos);
        bool IsCheckmate();


        bool IsInsideTheBoard(Pos pos);

    };
} // namespace DawnBoard::Chess
