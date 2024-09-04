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
	Game(std::map<LoggedUser, GameData> players, std::list<Question> questions);
	Question getQuestionForUser(LoggedUser user);
	int submitAnswer(LoggedUser user, int answer, float time);
	int removePlayer(LoggedUser user);
	int submitGameStatsToDB(std::map<LoggedUser, GameData> m_players, int m_gameId);
	static int m_gameId;

private:
	std::list<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	
};