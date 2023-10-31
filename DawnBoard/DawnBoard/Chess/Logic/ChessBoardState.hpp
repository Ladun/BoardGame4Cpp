#pragma once

#include <memory>
#include <set>

#include <DawnBoard/Base/DataStruct.hpp>
#include <DawnBoard/Chess/Object/ChessObject.hpp>

namespace DawnBoard::Chess
{

    using ChessObjectRef = std::shared_ptr<ChessObject>;

    struct ChessBoardState : public FieldState
    {        
        ChessObjectRef square[8][8] = {0, };
        std::vector<ChessObjectRef> pieces;

        // For checkmate or check ...
        std::set<Pos> possiblePositions[2];

        // Check for en passant
        Pos lastPawnPos     = {-1, -1};
        
        // Check for castling
        bool kingMoved[2]   = {false, false};
    };
} // namespace DawnBoard::Chess
