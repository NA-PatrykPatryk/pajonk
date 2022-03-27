#pragma once
#include <vector>
#include "../include/Directions.hpp"
#include "../include/Colors.hpp"

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
	Position getPrevPosition();
	void setDirection(DIRECTION);
	void move();

private:
	DIRECTION m_direction;
	Position m_position;
	Position m_prevPosition;
};