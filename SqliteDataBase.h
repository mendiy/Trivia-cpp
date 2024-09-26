#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include "Game.h"

class SqliteDataBase : public IDatabase
{
public:
    SqliteDataBase();
    ~SqliteDataBase();
    bool Open();
    bool Close();
    bool DoesUserExist(std::string username);
    bool DoesPasswordMatch(std::string password, std::string username);
    bool AddNewUser(std::string username, std::string password, std::string email);
    std::list<Question> GetQuestions(int amount);
    float GetPlayerAverageAnswerTime(std::string username);
    int GetNumOfCorrectAnswers(std::string username);
    int GetNumOfTotalAnswers(std::string username);
    int GetNumOfPlayerGames(std::string username);
    int GetPlayerScore(std::string username);
    std::vector<std::string> GetHighScores();
    void PrintQuestions(std::list<Question> questionList);
    int SubmitGameStatistics(std::map<LoggedUser, GameData> m_players, int gameId);


    sqlite3* db;
};