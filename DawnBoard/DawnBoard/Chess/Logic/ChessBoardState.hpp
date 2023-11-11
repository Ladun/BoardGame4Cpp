#pragma once

#include <memory>
#include <set>
#include <map>

#include <DawnBoard/Base/DataStruct.hpp>
#include <DawnBoard/Chess/Object/ChessObject.hpp>

namespace DawnBoard::Chess
{

    using ChessObjectRef = std::shared_ptr<ChessObject>;

    struct BoardInfo
    {
        ChessObjectRef piece = nullptr;
        bool boardSelected = false;

    };

    struct ChessBoardState : public FieldState
    {        
        BoardInfo square[8][8];
        // without king
        std::vector<ChessObjectRef> pieces;
        ChessObjectRef kings[2];
        
        // Current state;
        std::shared_ptr<ChessObject> selectedObj = {};

        // Check for en passant
        Pos lastPawnPos     = {-1, -1};
    };
} // namespace DawnBoard::Chess
