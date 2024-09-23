#include "Game.h"


Game::Game(std::map<LoggedUser, GameData> players, std::list<Question> questions, unsigned int ID)
{
    m_players = players;
    m_questions = questions;
    m_id = ID;
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

int Game::submitAnswer(LoggedUser user, int answer, float time)
{
    int currentCount = m_players[user].correctAnswerCount + m_players[user].wrongAnswerCount;
    float newAverage = ((m_players[user].averangeAnswerTime * currentCount) + time) / (currentCount + 1);
    m_players[user].averangeAnswerTime = newAverage;

   int correct = m_players[user].currentQuestion.getCorrectAnswerId();
   if (correct == answer)
    {
        m_players[user].correctAnswerCount++;
        return correct;
    }
    m_players[user].wrongAnswerCount++;
    return correct;
}

int Game::removePlayer(LoggedUser user)
{
    m_players.erase(user);
    return 0;
}

int Game::submitGameStatsToDB(std::map<LoggedUser, GameData> m_players, int id)
{
    return 0;
}

unsigned int Game::getId()
{
    return 0;
}
