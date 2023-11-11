#pragma once

#include <DawnStar/DawnStar.hpp>
#include <DawnBoard/Chess/Object/ChessObject.hpp>

using namespace DawnStar;
using namespace DawnBoard::Chess;

#pragma region Chess graphical component
struct ChessPieceComponent
{
    Ref<ChessObject> piece;    
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

};