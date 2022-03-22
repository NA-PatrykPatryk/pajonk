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
    Board(std::string);
public:
    SYMBOL& at(int, int);
    void makePermanent();
    std::string getBoard();
    void fill();
    void fill(int, int);
    bool isSurrounded(int, int);
    int size();
private:
    bool isSurrounded(int, int, std::vector<std::vector<SYMBOL>>&);
    bool inRange(int, int);
	std::string getRow(int rowNumber);
    void rotateBoard();
private:
    std::vector<std::vector<SYMBOL>> m_board{ };
};
