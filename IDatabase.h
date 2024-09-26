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
    virtual bool Open() = 0;
    virtual bool Close() = 0;
    virtual bool DoesUserExist(std::string) = 0;
    virtual bool DoesPasswordMatch(std::string, std::string) = 0;
    virtual bool AddNewUser(std::string, std::string, std::string) = 0;
    virtual std::list<Question> GetQuestions(int) = 0;
    virtual float GetPlayerAverageAnswerTime(std::string time) = 0;
    virtual int GetNumOfCorrectAnswers(std::string) = 0;
    virtual int GetNumOfTotalAnswers(std::string) = 0;
    virtual int GetNumOfPlayerGames(std::string) = 0;
    virtual int GetPlayerScore(std::string) = 0;
    virtual std::vector<std::string> GetHighScores() = 0;
    virtual int SubmitGameStatistics(std::map<LoggedUser, GameData> m_players, int gameId) = 0;
};