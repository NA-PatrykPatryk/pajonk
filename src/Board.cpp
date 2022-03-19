#include "Board.hpp"

Board::Board(int size) : m_size{size} {}

int Board::size()
{
    return m_size;
}