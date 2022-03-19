#include "Player.hpp"

// bool Position::operator==(const Position& rhs)
// {
//     return m_x == rhs.m_x && m_y == rhs.m_y;
// }

Player::Player(Position startPosition)
    : m_position(startPosition)
{}

Position Player::getPosition()
{
    return m_position;
}

void Player::moveUp() {
	++m_position.m_y;
}
void Player::moveRight() {
	++m_position.m_x;
}
void Player::moveDown() {
	--m_position.m_y;
}
void Player::moveLeft() {
	--m_position.m_x;
}
