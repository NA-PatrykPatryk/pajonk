#include "Board.hpp"

Board::Board(int size) 
    : m_size{size}
    , m_board(size, std::vector(size, SYMBOL::EMPTY))
    {}

SYMBOL& Board::at(int x, int y)
{
    return m_board.at(x).at(y);
}

void Board::makePermanent()
{
    for(auto& vec : m_board)
    {
        for(auto& symbol: vec)
        {
            if(symbol == SYMBOL::TAIL) symbol = SYMBOL::BODY;
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
    if(at(x, y) != SYMBOL::BODY)
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

std::string Board::getRow(int rowNumber) {
	std::string row{};
	for(int i{0}; i < m_size; ++i) {
		row += static_cast<char>(at(i, rowNumber));
	}
	return row;
}
