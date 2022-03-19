#pragma once
#include <string>
#include <vector>

enum class SYMBOL : char
{
    EMPTY = '.',
    HEAD = 'O',
    TAIL = 'o',
    BODY = 'X'
};

class Board
{
public:
    Board(int = 20);
public:
    SYMBOL& at(int, int);
    int size();
    std::string getBoard();
private:
    int m_size {};
    char returnCharacter(SYMBOL);
private:
    std::vector<std::vector<SYMBOL>> m_board{ };
};
