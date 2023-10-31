#pragma once

#include <DawnBoard/Chess/Utils.hpp>
#include <DawnBoard/Base/Object.hpp>

namespace DawnBoard::Chess
{
    enum class PieceType : uint8_t {
        PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
    };

    enum class PieceColor: uint8_t {
        BLACK=0, WHITE=1
    };

    class ChessObject : public Object
    {
    public:
        ChessObject(Pos pos, PieceType type, PieceColor color);
        
        Pos m_Pos;
        PieceType m_PieceType;
        PieceColor m_Color;

    };
} // namespace DawnBoard::Chess