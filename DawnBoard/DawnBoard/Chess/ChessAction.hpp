#pragma once

#include <DawnBoard/Base/DataStruct.hpp>
#include <DawnBoard/Chess/ChessObject.hpp>
#include <DawnBoard/Chess/Utils.hpp>

namespace DawnBoard::Chess
{
    enum class ActionType : uint8_t{
        SELECT, MOVE
    };
    
    struct ChessAction : public Action
    {
        ActionType type;
        PieceColor color;

        ChessAction(ActionType t, PieceColor c): type(t), color(c) {}
    };

    struct SelectAction : public ChessAction
    {
        Pos pos;
        SelectAction(Pos p, PieceColor c) 
            : ChessAction(ActionType::SELECT, c), pos(p) {}
    };

    struct MoveAction : public ChessAction
    {
        Pos dst;
        MoveAction(Pos p, PieceColor c)
            : ChessAction(ActionType::MOVE, c), dst(p) {}
    };
} // namespace DawnBoard::Chess
