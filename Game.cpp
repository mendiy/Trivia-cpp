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

int Game::submitAnswer(LoggedUser user, int answer, time_t time)
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

int Game::submitGameStatsToDB(std::map<LoggedUser, GameData> m_players, int id, IDatabase* m_database)
{
    int res = m_database->submitGameStatistics(m_players, id);
   
    return res;
}

unsigned int Game::getId()
{
    return m_id;
}

bool Game::gameIsFinished()
{
    int questionAmount = m_questions.size();
    for (auto it = m_players.begin(); it != m_players.end(); it++)
    {
        int correct = it->second.correctAnswerCount;
        int incorrect = it->second.wrongAnswerCount;
        if ( (correct + incorrect)  != questionAmount)
        {
            return false;
        }
    }
  
    return true;
}
