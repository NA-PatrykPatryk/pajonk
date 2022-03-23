#include "Board.hpp"
#include <iostream>

Board::Board(int size)
    : m_board(size, std::vector(size, Tile()))
    {}

Board::Board(std::string boardState)
{
    std::vector<Tile> temp;
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

Tile& Board::at(int x, int y)
{
    return m_board.at(x).at(y);
}

void Board::makePermanent()
{
    for (auto& vec : m_board)
    {
        for (auto& tile : vec)
        {
            if (tile.m_symbol == SYMBOL::TAIL) tile.m_symbol = SYMBOL::BODY;
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

void Board::printBoard()
{
    for (int i{ size() - 1 }; i >= 0; --i)
    {
        for (int j = 0; j < size(); ++j)
        {
            switch (at(j, i).m_color)
            {
            case COLOR::RED:
                std::cout << "\033[1;31m";
                break;
            case COLOR::GREEN:
                std::cout << "\033[1;32m";        
                break;
            case COLOR::YELLOW:
                std::cout << "\033[1;33m";        
                break;
            case COLOR::BLUE:
                std::cout << "\033[1;34m";        
                break;
            default:
                std::cout << "\033[1;37m";  
                break;
            }
            std::cout << static_cast<char>(at(j, i).m_symbol)
                      << "\033[0m";
        }
        std::cout << std::endl;
    }
}

void Board::fill()
{
    makePermanent();
    for(int y = 0; y < size(); ++y)
    {
        for(int x = 0; x < size(); ++x)
        {
            if(at(x, y).m_symbol == SYMBOL::EMPTY) //optimization thing
                if(isSurrounded(x, y)) 
                    fill(x, y);
        }
    }
}

void Board::fill(int x, int y)
{
    if (at(x, y).m_symbol != SYMBOL::BODY)
    {
        at(x, y).m_symbol = SYMBOL::BODY;
        fill(x - 1, y);
        fill(x + 1, y);
        fill(x, y - 1);
        fill(x, y + 1);
    }
}

bool Board::isSurrounded(int x, int y)
{
    std::vector<std::vector<Tile>> board = m_board;

    return isSurrounded(x, y, board);
}

bool Board::isSurrounded(int x, int y, std::vector<std::vector<Tile>>& boardC)
{
    if (not inRange(x, y)) return false;
    if (boardC.at(x).at(y).m_symbol == SYMBOL::CHECKED) return true;

    if (boardC.at(x).at(y).m_symbol != SYMBOL::BODY )
    {
        boardC.at(x).at(y).m_symbol = SYMBOL::CHECKED;
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
        row += static_cast<char>(at(i, rowNumber).m_symbol);
    }
    return row;
}

void Board::rotateBoard()
{
    for (int y = 0; y < size() / 2; ++y) 
    { 
        for (int x = y; x < size() - y - 1; ++x) 
        { 
            SYMBOL temp = at(y, x).m_symbol; 
            at(y, x) = at(size() - 1 - x, y); 
            at(size() - 1 - x, y) = at(size() - 1 - y, size() - 1 - x); 
            at(size() - 1 - y, size() - 1 - x) = at(x, size() - 1 - y); 
            at(x, size() - 1 - y) = temp; 
        } 
    }
}