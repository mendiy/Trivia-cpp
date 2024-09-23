#pragma once
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "LoginManager.h"
#include "MenuRequestHandler.h"
#include "StatisticsManager.h"
#include "RoomManager.h"
#include "LoggedUser.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser); 
	RoomAdminRequestHandler* createRoomAdminHandler(LoggedUser, Room); 
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser, Room); 
	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	StatisticsManager& getStatisticsManager();
private:
	LoginManager _loginManager;
	RoomManager _roomManager;
	StatisticsManager _statisticsManager;
	IDatabase* _database;
};