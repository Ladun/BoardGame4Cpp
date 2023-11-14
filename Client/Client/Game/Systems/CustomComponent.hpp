#pragma once

#include <DawnStar/DawnStar.hpp>
#include <DawnBoard/Chess/ChessObject.hpp>

using namespace DawnStar;
using namespace DawnBoard::Chess;

#pragma region Chess graphical component
struct ChessPieceComponent
{
    ChessObjectRef piece;    
};

struct ChessBoardComponent
{
    int8_t x, y;
};
#pragma endregion

struct TestComponent
{
    int val1;  
};

struct IndicatorComponent
{
	int posX, posY;
    
    int testIdx = 0;

};