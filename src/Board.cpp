#include "Board.hpp"

Board::Board(int size) 
    : m_size{size}
    , m_board(size, std::vector(size, SYMBOL::EMPTY))
    {}

SYMBOL& Board::at(int x, int y)
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
        for (auto symbol : vec)
        {
            board += returnCharacter(symbol);
        }

        board += '\n';
    }

    return board;
}

char Board::returnCharacter(SYMBOL symbol)
{
    switch(symbol)
    {
        case SYMBOL::EMPTY:
            return '.';
        case SYMBOL::HEAD:
            return 'O';
        case SYMBOL::TAIL:
            return 'o';
        case SYMBOL::BODY:
            return 'X';
    }
}