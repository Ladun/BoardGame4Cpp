#pragma once

#include <DawnBoard/Chess/Utils.hpp>
#include <DawnBoard/Base/Object.hpp>

namespace DawnBoard::Chess
{
    enum class PieceType {
        PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
    };

    enum class Color {
        BLACK, WHITE
    };

    class ChessObject : public Object
    {
    public:
        ChessObject(Pos pos, PieceType type, Color color);


        // TODO:: ChessField쪽으로 이동.
        std::vector<Pos> GetPossiblePosition();
    
    protected:
        Pos m_Pos;
        PieceType m_PieceType;
        Color m_Color;
    };
} // namespace DawnBoard::Chess