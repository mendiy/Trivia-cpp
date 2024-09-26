#include "StatisticsManager.h"
#include <string>
#include <iostream>

StatisticsManager::StatisticsManager(IDatabase* database)
{
    m_database = database;
}

std::vector<std::string> StatisticsManager::GetHighScore()
{
    std::lock_guard<std::mutex> lock(m_statisticMutex);
    return m_database->GetHighScores();
}

std::vector<std::string> StatisticsManager::GetUserStatistics(std::string username)
{
    std::lock_guard<std::mutex> lock(m_statisticMutex);
    std::vector<std::string> res;
    float average = m_database->GetPlayerAverageAnswerTime(username);
    int totalAnswers = m_database->GetNumOfTotalAnswers(username);
    int correctAnswers = m_database->GetNumOfCorrectAnswers(username);
    int sumOfGames = m_database->GetNumOfPlayerGames(username);
    int totalScore = m_database->GetPlayerScore(username);

    res.push_back("Player Average Answer Time: " + std::to_string(average));
    res.push_back("Num Of Total Answers: " + std::to_string(totalAnswers));
    res.push_back("Num Of Correct Answers: " + std::to_string(correctAnswers));
    res.push_back("Num Of Player Games: " + std::to_string(sumOfGames));
    res.push_back("Player Score: " + std::to_string(totalScore));
    return res;
}
