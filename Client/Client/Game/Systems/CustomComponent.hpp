#pragma once

#include <DawnStar/DawnStar.hpp>
#include <DawnBoard/Chess/ChessObject.hpp>

using namespace DawnStar;
using namespace DawnBoard::Chess;

#pragma region Chess graphical component
struct ChessPieceComponent
{
    ChessObjectRef piece;
    // For animation
    Pos currentPos;
    bool doAnimation = false;
    float time = 0.0f;
    float animTime = 0.3f;
};

struct ChessBoardComponent
{
    int8_t x, y;
    bool back=false;
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