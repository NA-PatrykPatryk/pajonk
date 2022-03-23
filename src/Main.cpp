#include <iostream>
#include <string>
#include <vector>
#include "Board.hpp"

int main()
{
    Board board{ 4 };
    board.at(0, 0) = SYMBOL::HEAD;
    std::cout << board.getBoard();

    std::cout << '\n';

    board.at(0, 1) = SYMBOL::BODY;
    std::cout << board.getBoard();
    
    std::cout << '\n';

    std::cout << "\033[1;31m"
                << "███\tRED"
                << "\033[0m \n";

    std::cout << "\033[1;32m"
                << "███\tGREEN"
                << "\033[0m \n";

    std::cout << "\033[1;33m"
                << "███\tYELLOW"
                << "\033[0m \n";

    std::cout << "\033[1;34m"
                << "███\tBLUE"
                << "\033[0m \n";

    std::cout << "\033[1;37m"
                << "███\tWHITE"
                << "\033[0m \n";

    Board sut1(".....\n"
               ".XXX.\n"
               "X...o\n"
               "X...o\n"
               ".XXX.\n");

    sut1.printBoard();    

    return 0;
}