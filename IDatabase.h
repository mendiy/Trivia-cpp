#pragma once
#include <iostream>
#include <list>
#include <map>
#include "Question.h"
#include "Game.h"

struct GameData;
//class Game;

class IDatabase
{
public: 
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual bool doesUserExist(std::string) = 0;
	virtual bool doesPasswordMatch(std::string, std::string) = 0;
	virtual bool addNewUser(std::string, std::string, std::string) = 0;
	virtual std::list<Question> getQuestions(int) = 0;
	virtual float getPlayerAverageAnswerTime(std::string time) = 0;
	virtual int getNumOfCorrectAnswers(std::string) = 0;
	virtual int getNumOfTotalAnswers(std::string) = 0;
	virtual int getNumOfPlayerGames(std::string) = 0;
	virtual int getPlayerScore(std::string) = 0;
	virtual std::vector<std::string> getHighScores() = 0;
	virtual int submitGameStatistics(std::map<LoggedUser, GameData> m_players, int gameId) = 0;
};