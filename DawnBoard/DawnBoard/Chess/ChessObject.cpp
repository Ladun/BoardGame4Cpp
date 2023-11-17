
#include <DawnBoard/Chess/ChessObject.hpp>
#include "ChessObject.hpp"

namespace DawnBoard::Chess
{
    ChessObject::ChessObject(Pos pos, PieceType type, PieceColor color)
        : m_Pos(pos), m_PieceType(type), m_Color(color), 
          m_Moved(false), m_Captured(false), m_CanMove(true)
    {

    }

    int PieceColorToInt(PieceColor c)
    { 
        return static_cast<int>(c);
    }
    PieceColor IntToPieceColor(int c) 
    { 
        return static_cast<PieceColor>(c);
    }

} // namespace DawnBoard