#include "Game.h"

int Game::m_gameId;


Game::Game(std::unordered_map<LoggedUser, GameData> players, std::list<Question> questions)
{
    m_players = players;
    m_questions = questions;
    m_gameId++;
}

Question Game::getQuestionForUser(LoggedUser user)
{

    for (auto it = m_questions.begin(); it != m_questions.end(); it++)
    {
        if (it->getQuestion() == m_players[user].currentQuestion.getQuestion())
        {
            it++;
            if (it != m_questions.end())
            {
               m_players[user].currentQuestion = *it;
                return *it;
            }
        }
    }
    return Question();
}

int Game::submitAnswer(LoggedUser user, int answer)
{
   int correct = m_players[user].currentQuestion.getCorrectAnswerId();
   if (correct == answer)
    {
        m_players[user].correctAnswerCount++;
        return 0;
    }
    m_players[user].wrongAnswerCount++;
    return 1;
}

int Game::removePlayer(LoggedUser user)
{
    m_players.erase(user);
    return 0;
}

int Game::submitGameStatsToDB(GameData data)
{
    return 0;
}
