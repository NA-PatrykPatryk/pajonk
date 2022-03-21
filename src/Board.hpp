#pragma once
#include <string>
#include <vector>

enum class SYMBOL : char
{
    EMPTY = '.',
    HEAD = 'O',
    TAIL = 'o',
    BODY = 'X',
    CHECKED = 'C'
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
    bool isSurrounded(int, int);
private:
    bool isSurrounded(int, int, std::vector<std::vector<SYMBOL>>&);
    bool inRange(int, int);
    char returnCharacter(SYMBOL);
	std::string getRow(int rowNumber);
private:
    std::vector<std::vector<SYMBOL>> m_board{ };
};
