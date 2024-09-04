#pragma once
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "LoginManager.h"
#include "MenuRequestHandler.h"
#include "StatisticsManager.h"
#include "RoomManager.h"
#include "LoggedUser.h"

//class RoomManager{}; // for test
//class StatisticsManager{
//public:
//	StatisticsManager(IDatabase* database) : _database(database) {};
//private:
//	IDatabase* _database;
//}; // for test

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser); 
	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	StatisticsManager& getStatisticsManager();
private:
	LoginManager _loginManager;
	RoomManager _roomManager;
	StatisticsManager _statisticsManager;
	IDatabase* _database;
};