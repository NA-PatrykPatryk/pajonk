#pragma once
#include <vector>

struct Position
{
	// friend bool operator==(const Position& lhs, const Position& rhs)
	// {
	// 	return lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y;
	// }

	bool operator==(const Position& rhs) const
	{
		return m_x == rhs.m_x && m_y == rhs.m_y;
	}

	int m_x{};
	int m_y{};
};

class Player
{
public:
	Player(Position startPosition);
	Position getPosition();
	void moveUp();
private:
	Position m_position;
};
