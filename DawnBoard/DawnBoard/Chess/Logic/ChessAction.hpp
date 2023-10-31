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
    };

    struct MoveAction : public ChessAction
    {
        Pos st;
        Pos ed;
    };
} // namespace DawnBoard::Chess
