#include "GameManager.h"
#include <algorithm>
#include <exception>


Game& GameManager::CreateGame(Room room)
{
    std::map<LoggedUser, GameData> game;
    std::vector<std::string> users = room.GetAllUsers();
    std::for_each(users.begin(), users.end(), [&](std::string user) {
        LoggedUser u(user);
        game[u] = GameData();
    });
   
    std::list<Question> questions = m_database->GetQuestions(room.GetRoom().numOfQuestionsInGame);
    Game newGame(game, questions, room.GetRoom().id);
    m_games.push_back(newGame);
    return m_games[m_games.size() - 1];
}

void GameManager::DeleteGame(int gameId)
{
    for (auto it = m_games.begin(); it != m_games.end(); it++)
    {
        if (it->getId() == gameId)
        {
            m_games.erase(it);
        } 
    }
}

Game& GameManager::GetGame(unsigned int id)
{
    for (auto it = m_games.begin(); it != m_games.end(); it++)
    {
        if (it->getId() == id)
        {
            return *it;
        }
    }
    throw(std::exception("game id not found"));
}
