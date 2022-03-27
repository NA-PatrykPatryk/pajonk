// #include "../include/Game.hpp"

// Game::Game(int playersCount) 
//     : m_board(), m_players(playersCount)
//     {}

// void Game::setUp()
// {
//     createPlayers();
//     populateBoard();
// }

// void Game::createPlayers()
// {
//     int pos = m_board.size() / 4;
//     if (m_players.size() == 1)
//     {
//         m_players.at(0) = Player({pos, pos}, COLOR::RED), DIRECTION::UP;
//     }
//     if (m_players.size() == 2)
//     {
//         m_players.at(1) = Player({3 * pos, pos}, COLOR::GREEN, DIRECTION::LEFT);
//     }
//     if (m_players.size() == 3)
//     {
//         m_players.at(2) = Player({pos, 3 * pos}, COLOR::YELLOW, DIRECTION::RIGHT);
//     }
//     if (m_players.size() == 4)
//     {
//         m_players.at(3) = Player({3 * pos, 3 * pos}, COLOR::BLUE), DIRECTION::DOWN;
//     }
// }

// void Game::populateBoard()
// {
//     for(auto p : m_players)
//     {
//         p.getPosition().m_x;
//         p.getPosition().m_y;
//     }
// }