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
	Player(Position = {0, 0}, COLOR = COLOR::WHITE, DIRECTION = DIRECTION::UP);
	Position getPosition() const;
	Position getPrevPosition() const;
	COLOR getColor() const;
	void setDirection(DIRECTION);
	void move();

private:
	Position m_position;
	Position m_prevPosition;
	COLOR m_color;
	DIRECTION m_direction;
};