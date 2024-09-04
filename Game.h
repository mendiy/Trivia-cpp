#pragma once
#include<iostream>
#include <vector>
#include <map>
#include "LoggedUser.h"
#include "Question.h"
#include <iostream>
#include <list>
#include <unordered_map>



struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averangeAnswerTime;
}; GameData;

class Game
{
public:
	Game(std::unordered_map<LoggedUser, GameData> players, std::list<Question> questions);
	Question getQuestionForUser(LoggedUser user);
	int submitAnswer(LoggedUser user, int answer);
	int removePlayer(LoggedUser user);
	int submitGameStatsToDB(GameData data);
	static int m_gameId;

private:
	std::list<Question> m_questions;
	std::unordered_map<LoggedUser, GameData> m_players;
	
};