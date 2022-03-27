#pragma once
#include "Board.hpp"
#include "Player.hpp"

class Game
{
public:
    Game(int = 1);
public:
    void setUp();
    void draw();
private:
    void populateBoard();
    void createPlayers();
private:
    Board m_board;
    std::vector<Player> m_players;
};