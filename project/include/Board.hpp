#pragma once
#include <string>
#include <vector>
#include "../include/Colors.hpp"
#include "../include/Symbols.hpp"

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
    Board(int = 12);
    Board(std::string);
public:
    Tile& at(int, int);
    void printBoard();
    std::string getBoard();
    void fill(COLOR = COLOR::WHITE);
    void populate(int, int, COLOR);
    int size();
private:
    void fill(int, int, COLOR = COLOR::WHITE);
    void makePermanent(COLOR = COLOR::WHITE);
    bool isSurrounded(int, int, std::vector<Tile>&, COLOR = COLOR::WHITE);
    bool inRange(int, int);
    int reverse(int);
private:
    int m_size {};
    std::vector<Tile> m_board {};
};
