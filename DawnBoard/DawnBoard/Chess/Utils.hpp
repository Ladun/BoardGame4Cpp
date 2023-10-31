#pragma once

#include <cstdint>
#include <vector>

#define BIT(x) (1 << x)

namespace DawnBoard::Chess
{   

    struct Pos
    {
        int8_t x, y;
        Pos(int8_t _x, int8_t _y): x(_x), y(_y) {}
        Pos(int _x, int _y): x(_x), y(_y) {}

        Pos operator+(const Pos& o)
        {
            return Pos(x + o.x, y + o.y);
        }
        Pos operator-(const Pos& o)
        {
            return Pos(x - o.x, y - o.y);
        }
        
        Pos operator+=(const Pos& o)
        {
            (*this) = (*this) + o;
            return *this;
        }
    };
} // namespace DawnBoard::Chess
