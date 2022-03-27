#include "../include/Board.hpp"
#include <iostream>

Board::Board(int size)
    :  m_size{size}, m_board(size * size, Tile())
    {}

Board::Board(std::string boardState) : m_board {}
{
    for(size_t i = 1; i < boardState.length(); ++i)
    {
        if(boardState.at(i) == '\n')
        {
            m_size = i;
            break;
        }
    }
    m_board.reserve(boardState.length());
    for(auto& c : boardState)
    {
        if(c == '.') m_board.push_back(SYMBOL::EMPTY);
        if(c == 'X') m_board.push_back(SYMBOL::BODY);
        if(c == 'o') m_board.push_back(SYMBOL::TAIL);
        if(c == 'O') m_board.push_back(SYMBOL::HEAD);
    }
}

Tile& Board::at(int x, int y)
{
    return m_board.at(x + reverse(y) * size());
}

void Board::printBoard()
{
    for (size_t i = 0; i < m_board.size(); ++i)
    {
        switch (m_board.at(i).m_color)
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
        std::cout << static_cast<char>(m_board.at(i).m_symbol)
                  << "\033[0m";
        if ((i + 1) % (size()) == 0) std::cout << std::endl;
    }
}

std::string Board::getBoard()
{
    std::string board{};

    for (size_t i = 0; i < m_board.size(); ++i)
    {
        board += static_cast<char>(m_board.at(i).m_symbol);
        if ((i + 1) % (size()) == 0) 
            board += '\n';
    }

    return board;
}

void Board::fill(COLOR color)
{
    makePermanent(color);
    std::vector<Tile> boardC = m_board;
    for(int x = 0; x < size(); ++x)
    {
        for(int y = 0; y < size(); ++y)
        {
            if(boardC.at(x + reverse(y) * size()).m_symbol == SYMBOL::EMPTY)
                if(isSurrounded(x, y, boardC, color)) 
                    fill(x, y, color);
        }
    }
}

int Board::size()
{
    return m_size;
}

void Board::fill(int x, int y, COLOR color)
{
    if (at(x, y).m_symbol == SYMBOL::BODY && at(x, y).m_color == color) return;
    
    at(x, y).m_symbol = SYMBOL::BODY;
    at(x, y).m_color = color;
    fill(x - 1, y, color);
    fill(x + 1, y, color);
    fill(x, y - 1, color);
    fill(x, y + 1, color);
}

void Board::makePermanent(COLOR color)
{
    for (auto& tile : m_board)
    {
        if (tile.m_symbol == SYMBOL::TAIL && tile.m_color == color) 
            tile.m_symbol = SYMBOL::BODY;
    }
}

bool Board::isSurrounded(int x, int y, std::vector<Tile>& boardC, COLOR color)
{
    if (not inRange(x, y)) return false;
    if (boardC.at(x + reverse(y) * size()).m_symbol == SYMBOL::CHECKED) return true;

    if (boardC.at(x + reverse(y) * size()).m_symbol == SYMBOL::BODY 
    && boardC.at(x + reverse(y) * size()).m_color == color) return true;

    boardC.at(x + reverse(y) * size()).m_symbol = SYMBOL::CHECKED;
    bool left = isSurrounded(x - 1, y, boardC, color);
    bool right = isSurrounded(x + 1, y, boardC, color);
    bool down = isSurrounded(x, y - 1, boardC, color);
    bool up = isSurrounded(x, y + 1, boardC, color);

    return left && right && down && up;

}

bool Board::inRange(int x, int y)
{
    return x >= 0 and x < size() and y >= 0 and y < size();
}

int Board::reverse(int y)
{
    return (size() - 1 - y);
}