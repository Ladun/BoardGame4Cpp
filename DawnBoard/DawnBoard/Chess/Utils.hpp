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
        Pos(float _x, float _y): x(_x), y(_y) {}

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

        bool operator==(const Pos& o)
        {
            return x == o.x && y == o.y;
        }
        
        bool operator!=(const Pos& o)
        {
            return x != o.x || y != o.y;
        }        

        bool operator < (const Pos& o) const {
            return (x != o.x ? x < o.x : y < o.y);
        }

        // Whether the three position are in a line
        static bool OnLine(Pos p1, Pos p2, Pos p3)
        {
            // a = (p1.y - p2.y) / (p1.x - p2.x) = (p2.y - p3.y) / (p2.x - p3.y)
            // -> (p1.y - p2.y) * (p2.x - p3.y) = (p2.y - p3.y) * (p1.x - p2.x)
            // -> dy1 * dx2 == dy2 * dx1

            int dy1 = p1.y - p2.y;
            int dx1 = p1.x - p2.x;
            int dy2 = p2.y - p3.y;
            int dx2 = p2.x - p3.x;

            return dy1 * dx2 == dy2 * dx1;
        }
    };
} // namespace DawnBoard::Chess
