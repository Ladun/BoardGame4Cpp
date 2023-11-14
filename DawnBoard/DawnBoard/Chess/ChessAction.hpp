#pragma once

#include <DawnBoard/Base/DataStruct.hpp>
#include <DawnBoard/Chess/Utils.hpp>

namespace DawnBoard::Chess
{
    enum class ActionType : uint8_t{
        SELECT, MOVE
    };
    
    struct ChessAction : public Action
    {
        ActionType type;
    };

    struct SelectAction : public ChessAction
    {
        Pos pos;
        SelectAction(Pos p) : pos(p) { type = ActionType::SELECT; }
    };

    struct MoveAction : public ChessAction
    {
        Pos dst;
        MoveAction(Pos p) : dst(p) { type = ActionType::MOVE; }
    };
} // namespace DawnBoard::Chess