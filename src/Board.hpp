#pragma once
#include <string>
#include <vector>

class Board
{
public:
    Board(int = 20);
public:
    char at(int, int);
    int size();
    std::string getBoard();
private:
    int m_size {};
    std::vector<std::vector<char>> m_board{ };
};
