#pragma once

#include <DawnBoard/Chess/Utils.hpp>
#include <DawnBoard/Base/Object.hpp>

#include <vector>
#include <memory>

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
        bool m_Moved;
        bool m_Captured;
        
        std::vector<Pos> m_AvailablePos;
        std::vector<Pos> m_KillerPos; //position of which can capture this piece
    };
    using ChessObjectRef = std::shared_ptr<ChessObject>;
} // namespace DawnBoard::Chess