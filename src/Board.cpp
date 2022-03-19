#include "Board.hpp"

Board::Board(int size) 
    : m_size{size}
    , m_board(size, std::vector(size, '.'))
    {}

char Board::at(int x, int y)
{
    return m_board.at(x).at(y);
}

int Board::size()
{
    return m_board.size();
}

std::string Board::getBoard()
{
    std::string board{};

    for (auto vec : m_board)
    {
        for (auto character : vec)
        {
            board += character;
        }

        board += '\n';
    }

    return board;
}