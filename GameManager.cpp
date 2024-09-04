#include "GameManager.h"
#include <algorithm>



Game GameManager::createGame(Room room)
{
    std::unordered_map<LoggedUser, GameData> game;
    std::vector<std::string> users = room.getAllUsers();
    std::for_each(users.begin(), users.end(), [&](std::string user) {
        LoggedUser u(user);
        game[u] = GameData();
    });
   
    std::list<Question> questions = m_database->getQuestions(room.getRoom().numOfQuestionsInGame);
    Game newGame(game, questions);
    m_games.push_back(newGame);
    return newGame;
}

void GameManager::deleteGame(int gameId)
{
    for (auto it = m_games.begin(); it != m_games.end(); it++)
    {
        if (it->m_gameId == gameId)
        {
            m_games.erase(it);
        } 
    }
}
