#include "../include/Player.hpp"

bool Position::operator==(const Position& rhs) const
{
    return m_x == rhs.m_x && m_y == rhs.m_y;
}


Player::Player(Position startPosition, COLOR color)
    : m_position(startPosition), m_color(color) 
    {}

Position Player::getPosition()
{
    return m_position;
}

Position Player::getPrevPosition()
{
    return m_prevPosition;
}

COLOR Player::getColor()
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