#include "Board.hpp"

Board::Board(int size)
    : m_board(size, std::vector(size, SYMBOL::EMPTY))
    {}

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

    for (int i{ size() - 1 }; i >= 0; --i)
    {
        board += getRow(i) + '\n';
    }

    return board;
}

void Board::fill()
{
    for(int y = 0; y < size(); ++y)
    {
        for(int x = 0; x < size(); ++x)
        {
            // if(at(x, y) == SYMBOL::EMPTY) optimization thing
                if(isSurrounded(x, y)) 
                    fill(x, y);
        }
    }
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

bool Board::isSurrounded(int x, int y)
{
    std::vector<std::vector<SYMBOL>> board = m_board;

    return isSurrounded(x, y, board);
}

bool Board::isSurrounded(int x, int y, std::vector<std::vector<SYMBOL>>& boardC)
{
    if (not inRange(x, y)) return false;
    if (boardC.at(x).at(y) == SYMBOL::CHECKED) return true;

    if (boardC.at(x).at(y) != SYMBOL::BODY )
    {
        boardC.at(x).at(y) = SYMBOL::CHECKED;
        bool left = isSurrounded(x - 1, y, boardC);
        bool right = isSurrounded(x + 1, y, boardC);
        bool down = isSurrounded(x, y - 1, boardC);
        bool up = isSurrounded(x, y + 1, boardC);

        return left && right && down && up;
    }
    return true;
}

int Board::size()
{
    return m_board.size();
}

bool Board::inRange(int x, int y)
{
    return x >= 0 and x < size() and y >= 0 and y < size();
}

std::string Board::getRow(int rowNumber) 
{
    std::string row{};
    for (int i{ 0 }; i < size(); ++i) {
        row += static_cast<char>(at(i, rowNumber));
    }
    return row;
}
