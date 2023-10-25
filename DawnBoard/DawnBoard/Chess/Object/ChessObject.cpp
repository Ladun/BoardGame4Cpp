
#include <DawnBoard/Chess/Object/ChessObject.hpp>
#include "ChessObject.hpp"

namespace DawnBoard::Chess
{
    ChessObject::ChessObject(Pos pos, PieceType type, Color color)
        : m_Pos(pos), m_PieceType(type), m_Color(color)
    {

    }


    std::vector<Pos> ChessObject::GetPossiblePosition()
    {
        std::vector<Pos> pos;
        switch(m_PieceType)
        {
        case PieceType::PAWN:
        {

            break;
        }
        case PieceType::ROOK:
        {

            break;
        }
        case PieceType::KNIGHT:
        {

            break;
        }
        case PieceType::BISHOP:
        {

            break;
        }
        case PieceType::KING:
        {

            break;
        }
        case PieceType::QUEEN:
        {

            break;
        }
        }

        return pos;
    }

} // namespace DawnBoard