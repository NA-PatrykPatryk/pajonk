#pragma once

#include<vector>

using Position = std::vector<int>;

struct Player {
	Player(Position startPosition) : m_position(startPosition) {}
	Position getPosition() {return m_position;}
	private:
	Position m_position;
};


