#include "../include/Player.hpp"

bool Position::operator==(const Position& rhs) const
{
    return m_x == rhs.m_x && m_y == rhs.m_y;
}


Player::Player(Position startPosition, COLOR color, DIRECTION direction)
    : m_position(startPosition), m_color(color), m_direction(direction)
    {}

Position Player::getPosition() const
{
    return m_position;
}

Position Player::getPrevPosition() const
{
    return m_prevPosition;
}

COLOR Player::getColor() const
{
    return m_color;
}

void Player::setDirection(DIRECTION direction)
{
    m_direction = direction;
}

void Player::move()
{
    m_prevPosition = m_position;
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