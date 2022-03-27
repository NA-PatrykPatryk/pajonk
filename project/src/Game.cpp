#include "../include/Game.hpp"

Game::Game(int playersCount) 
    : m_board(), m_players(playersCount)
    {}

void Game::setUp()
{
    createPlayers();
    populateBoard();
}

void Game::draw()
{
    m_board.printBoard();
}

void Game::createPlayers()
{
    int quarter = m_board.size() / 4;
    int pos1 = quarter;
    int pos2 = m_board.size() - quarter - 1;

    if(m_players.size() >= 1)
        m_players.at(0) = Player({pos1, pos1}, COLOR::RED, DIRECTION::UP);
    if(m_players.size() >= 2)
        m_players.at(1) = Player({pos2, pos1}, COLOR::GREEN, DIRECTION::LEFT);
    if(m_players.size() >= 3)
        m_players.at(2) = Player({pos1, pos2}, COLOR::YELLOW, DIRECTION::RIGHT);
    if(m_players.size() == 4)  
        m_players.at(3) = Player({pos2, pos2}, COLOR::BLUE, DIRECTION::DOWN);  
}

void Game::populateBoard()
{
    for(const auto& p : m_players)
    {
        m_board.populate(p.getPosition().m_x, p.getPosition().m_y, p.getColor());
    }
}