#include "Board.hpp"

Board::Board(int size)
    : m_board(size, std::vector(size, SYMBOL::EMPTY))
    {}

Board::Board(std::string boardState)
{
    std::vector<SYMBOL> temp;
    for(auto& c : boardState)
    {
        if(c == '.') temp.push_back(SYMBOL::EMPTY);
        else if(c == 'X') temp.push_back(SYMBOL::BODY);
        else if(c == 'o') temp.push_back(SYMBOL::TAIL);
        else if(c == 'O') temp.push_back(SYMBOL::HEAD);
        if(c == '\n')
        {
            m_board.push_back(temp);
            temp.clear();
        }
    }
    rotateBoard();
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

void Board::rotateBoard()
{
    for (int y = 0; y < size() / 2; ++y) 
    { 
        for (int x = y; x < size() - y - 1; ++x) 
        { 
            SYMBOL temp = at(y, x); 
            at(y, x) = at(size() - 1 - x, y); 
            at(size() - 1 - x, y) = at(size() - 1 - y, size() - 1 - x); 
            at(size() - 1 - y, size() - 1 - x) = at(x, size() - 1 - y); 
            at(x, size() - 1 - y) = temp; 
        } 
    }
}