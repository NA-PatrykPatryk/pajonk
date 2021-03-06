#pragma once
#include <vector>

enum class DIRECTION 
{
	UP, DOWN, LEFT, RIGHT
};

struct Position
{
	bool operator==(const Position& rhs) const;

	int m_x{};
	int m_y{};
};

class Player
{
public:
	Player(Position startPosition);
	Position getPosition();
	void setDirection(DIRECTION);
	// void checkDirectionBasedOnInput(Input input);
	void move();

private:
	Position m_position;
	DIRECTION m_direction;
};