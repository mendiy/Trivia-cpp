#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include "Game.h"

class SqliteDataBase : public IDatabase
{
public:
	SqliteDataBase();
	~SqliteDataBase();
	bool open();
	bool close();
	bool doesUserExist(std::string username);
	bool doesPasswordMatch(std::string password, std::string username);
	bool addNewUser(std::string username, std::string password, std::string email);
	std::list<Question> getQuestions(int amount);
	float getPlayerAverageAnswerTime(std::string username);
	int getNumOfCorrectAnswers(std::string username);
	int getNumOfTotalAnswers(std::string username);
	int getNumOfPlayerGames(std::string username);
	int getPlayerScore(std::string username);
	std::vector<std::string> getHighScores();
	void printQuestions(std::list<Question> questionList);
	int submitGameStatistics(std::string gameData);


	sqlite3* db;
};