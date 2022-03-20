#include "Board.hpp"

Board::Board(int size)
    : m_size{ size }
    , m_board(size, std::vector(size, SYMBOL::EMPTY))
{}

bool Board::inRange(int x, int y)
{
    return x >= 0 and x < size() and y >= 0 and y < size();
}

SYMBOL& Board::at(int x, int y)
{
    return m_board.at(x).at(y);
}

void Board::makePermanent()
{
    for (auto& vec : m_board)
    {
        for (auto& symbol : vec)
        {
            if (symbol == SYMBOL::TAIL) symbol = SYMBOL::BODY;
        }
    }
}

std::string Board::getBoard()
{
    std::string board{};

    for (int i{ m_size - 1 }; i >= 0; --i)
    {
        board += getRow(i) + '\n';
    }

    return board;
}

void Board::fill(int x, int y)
{
    if (at(x, y) != SYMBOL::BODY)
    {
        at(x, y) = SYMBOL::BODY;
        fill(x - 1, y);
        fill(x + 1, y);
        fill(x, y - 1);
        fill(x, y + 1);
    }
}

int Board::size()
{
    return m_board.size();
}

bool Board::isSurrounded(int x, int y)
{
    if (not inRange(x, y))
        return false;
    if (at(x, y) != SYMBOL::BODY)
        return true;
    
    bool left = isSurrounded(x - 1, y);
    bool right = isSurrounded(x + 1, y);
    bool down = isSurrounded(x, y - 1);
    bool up = isSurrounded(x, y + 1);

    return left and right and down and up;
}

std::string Board::getRow(int rowNumber) {
    std::string row{};
    for (int i{ 0 }; i < m_size; ++i) {
        row += static_cast<char>(at(i, rowNumber));
    }
    return row;
}
