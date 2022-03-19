#include <iostream>
#include <string>
#include <vector>
#include "Board.hpp"

int main()
{
    Board board{ 4 };
    board.at(0, 0) = SYMBOL::HEAD;
    std::cout << board.getBoard();

    board.at(0, 1) = SYMBOL::BODY;
    std::cout << board.getBoard();

    return 0;
}