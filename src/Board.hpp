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

enum class COLOR
{
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    WHITE = 37
};

struct Tile
{
    Tile(SYMBOL symbol = SYMBOL::EMPTY, COLOR color = COLOR::WHITE)
    : m_symbol(symbol), m_color(color)
    {}

    SYMBOL m_symbol;
    COLOR m_color;
};

class Board
{
public:
    Board(int = 20);
    Board(std::string);
public:
    Tile& at(int, int);
    void makePermanent();
    std::string getBoard();
    void printBoard();
    void fill(COLOR);
    void fill();
    void fill(int, int);
    void fill(int, int, COLOR);
    bool isSurrounded(int, int);
    int size();
private:
    bool isSurrounded(int, int, std::vector<std::vector<Tile>>&);
    bool isSurrounded(int, int, std::vector<std::vector<Tile>>&, COLOR);
    bool inRange(int, int);
	std::string getRow(int rowNumber);
    void rotateBoard();
private:
    std::vector<std::vector<Tile>> m_board{ };
};
