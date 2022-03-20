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
    void makePermanent();
    std::string getBoard();
    void fill(int, int);
    int size();
private:
    int m_size {};
    char returnCharacter(SYMBOL);
	std::string getRow(int rowNumber);
private:
    std::vector<std::vector<SYMBOL>> m_board{ };
};
