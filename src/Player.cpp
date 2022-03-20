#include "Player.hpp"

bool Position::operator==(const Position& rhs) const
{
    return m_x == rhs.m_x && m_y == rhs.m_y;
}


Player::Player(Position startPosition)
    : m_position(startPosition)
    {}

Position Player::getPosition()
{
    return m_position;
}

void Player::setDirection(DIRECTION direction)
{
    m_direction = direction;
}

void Player::setDirectionBasedOnChange(char change)
{
	switch(change) {
		case 'R' : setDirection(DIRECTION::RIGHT); return;
		case 'D' : setDirection(DIRECTION::DOWN); return;
		case 'L' : setDirection(DIRECTION::LEFT); return;
		case 'U' : setDirection(DIRECTION::UP); return;
	}
}

void Player::move()
{
    switch(m_direction)
    {
        case DIRECTION::UP:
            ++m_position.m_y;
            break;
        case DIRECTION::DOWN:
            --m_position.m_y;
            break;
        case DIRECTION::LEFT:
            --m_position.m_x;
            break;
        case DIRECTION::RIGHT:
            ++m_position.m_x;
            break;
    }
}
