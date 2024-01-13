#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;
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

	bool operator < (const Pos& o) const {
		return (x != o.x ? x < o.x : y < o.y);
	}
};


int main()
{
	set<Pos> positions;

	positions.insert({0, 0});
	positions.insert({0, 1});
	positions.insert({0, 2});
	positions.insert({0, 3});
	positions.insert({0, 4});

	auto iter = positions.find({0, 0});
	if(iter != positions.end())
	{
		cout << "Find!\n";
	}

	return 0;
}