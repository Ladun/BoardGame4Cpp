#pragma once

#include <vector>

#include <DawnBoard/Base/Field.hpp>
#include <DawnBoard/Chess/Object/ChessObject.hpp>
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
        bool IsAvailablePos(Pos pos);
        std::vector<Pos> GetPossiblePosition(Pos pos);

    private:
        std::shared_ptr<ChessObject> m_SelectedObj;
        std::vector<Pos> m_PossiblePos;

    };
} // namespace DawnBoard::Chess
