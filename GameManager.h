#pragma once
#include <iostream>
#include "IDatabase.h"
#include "Room.h"
#include "Game.h"
#include <vector>

class GameManager
{
public:
	GameManager(IDatabase* database) : m_database(database) {}
	Game createGame(Room room);
	void deleteGame(int gameId);
private:
	IDatabase* m_database;
	std::vector<Game> m_games;
};