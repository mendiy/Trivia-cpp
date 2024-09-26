#pragma once
#include <iostream>
#include <vector>
#include "IDatabase.h"
#include <mutex>

class StatisticsManager
{
public:
    StatisticsManager(IDatabase* m_database);
    std::vector<std::string> GetHighScore();
    std::vector<std::string> GetUserStatistics(std::string username);
private:
    IDatabase* m_database;
    std::mutex m_statisticMutex;

};