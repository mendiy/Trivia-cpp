#pragma once
#include<iostream>
#include <vector>
#include <map>
#include "LoggedUser.h"
#include "Question.h"
#include <iostream>
#include <list>
#include <unordered_map>
#include <memory>
#include "IDatabase.h"

class IDatabase;

struct GameData
{
    Question currentQuestion {Question()};
    unsigned int correctAnswerCount {0};
    unsigned int wrongAnswerCount {0};
    unsigned int averangeAnswerTime {0};
}; GameData;

class Game
{
public:
    Game(std::map<LoggedUser, GameData> players, std::list<Question> questions, unsigned int ID);
    Question GetQuestionForUser(LoggedUser user);
    int SubmitAnswer(LoggedUser user, int answer, time_t time);
    int RemovePlayer(LoggedUser user);
    int SubmitGameStatsToDB(std::map<LoggedUser, GameData> m_players, int m_gameId, IDatabase* m_database);
    unsigned int getId();
    bool GameIsFinished();
    inline std::map<LoggedUser, GameData> GetGameResults() { return m_players; };
private:
    
    std::list<Question> m_questions;
    std::map<LoggedUser, GameData> m_players;
    unsigned int m_id;
};