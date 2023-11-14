#pragma once

#include <memory>
#include <set>
#include <map>

#include <DawnBoard/Base/DataStruct.hpp>
#include <DawnBoard/Chess/ChessObject.hpp>

namespace DawnBoard::Chess
{

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
        Pos lastEnPassantPos    = {-1, -1};
        // Check state
        bool isCheck[2]         = {false, false};
        // Rendering value
        bool needRender         = false;
    };


    struct Movement
    {
        static const uint8_t CHECKABLE = 1;
        static const uint8_t ENPASSANT = 2;
        static const uint8_t CASTLING = 4;

        Pos pos;
        uint8_t state;
        // Add en passant state and castling state
    };
} // namespace DawnBoard::Chess
