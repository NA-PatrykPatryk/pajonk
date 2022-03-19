#include "Board.hpp"

Board::Board(int size) 
    : m_size{size}
    , m_board(size, std::vector(size, SYMBOL::EMPTY))
    {}

SYMBOL& Board::at(int x, int y)
{
    return m_board.at(y).at(x);
}

int Board::size()
{
    return m_board.size();
}

std::string Board::getBoard()
{
    std::string board{};

    for (int i{ m_size - 1 }; i >= 0; --i)
    {
        for (int j{ 0 }; j < m_size; ++j)
        {
            board += static_cast<char>(m_board[i][j]);
        }
        board += '\n';
    }

    return board;
}