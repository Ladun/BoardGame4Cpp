#pragma once

#include <vector>

#include <DawnBoard/Base/Field.hpp>
#include <DawnBoard/Chess/Object/ChessObject.hpp>
#include <DawnBoard/Chess/Logic/ChessBoardState.hpp>
#include <DawnBoard/Chess/Utils.hpp>

namespace DawnBoard::Chess
{
    class ChessBoard : public Field
    {
    public:
        virtual void Init();
        virtual void Start();
        virtual void Clear();

        virtual void ApplyAction(Action& action);

        int GetPieceCount();

    private:
        void UpdateBoardState();
        void UpdateAvailablePosition(ChessObjectRef& piece, std::set<Pos>& kingsAvailablePos);

        bool IsInsideTheBoard(Pos pos);

    };
} // namespace DawnBoard::Chess
