
#include <DawnBoard/Chess/ChessObject.hpp>
#include "ChessObject.hpp"

namespace DawnBoard::Chess
{
    ChessObject::ChessObject(Pos pos, PieceType type, PieceColor color)
        : m_Pos(pos), m_PieceType(type), m_Color(color), m_Moved(false)
    {

    }

} // namespace DawnBoard