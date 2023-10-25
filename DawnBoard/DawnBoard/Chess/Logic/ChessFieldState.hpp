#pragma once

#include <memory>

#include <DawnBoard/Base/DataStruct.hpp>
#include <DawnBoard/Chess/Object/ChessObject.hpp>

namespace DawnBoard::Chess
{
    struct ChessFieldState : public FieldState
    {
        std::shared_ptr<ChessObject> m_BoardState[8][8];
    };
} // namespace DawnBoard::Chess
