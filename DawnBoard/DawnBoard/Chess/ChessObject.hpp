#pragma once

#include <DawnBoard/Base/Object.hpp>
#include <DawnBoard/Chess/Utils.hpp>


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
    int PieceColorToInt(PieceColor c);
    PieceColor IntToPieceColor(int c);

    struct Movement
    {
        enum class State: uint8_t
        {
            NORMAL=0,
            ENPASSANT=1,
            CASTLING=2
        };

        Pos pos;
        State state;
        // Add en passant state and castling state
        Movement(Pos p, State s): pos(p), state(s) {}
    };

    class ChessObject : public Object
    {
    public:
        ChessObject(Pos pos, PieceType type, PieceColor color);

    public:        
        Pos m_Pos;
        PieceType m_PieceType;
        PieceColor m_Color;
        bool m_Moved;
        bool m_Captured;
        
        std::vector<Movement> m_AvailableMove;
        std::vector<Pos> m_KillerPos; //position of which can capture this piece
    };
    using ChessObjectRef = std::shared_ptr<ChessObject>;
} // namespace DawnBoard::Chess