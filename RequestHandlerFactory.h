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
#include "GameManager.h"
#include "GameRequestHandler.h"
#include "Game.h"

class RequestHandlerFactory
{
public:
    RequestHandlerFactory(IDatabase* database);
    LoginRequestHandler* createLoginRequestHandler();
    MenuRequestHandler* createMenuRequestHandler(LoggedUser); 
    RoomAdminRequestHandler* createRoomAdminHandler(LoggedUser, Room&); 
    RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser, Room&); 
    GameRequestHandler* createGameRequestHandler(LoggedUser, Game&);
    LoginManager& getLoginManager();
    RoomManager& getRoomManager();
    StatisticsManager& getStatisticsManager();
    GameManager& getGameManager();
private:
    LoginManager _loginManager;
    RoomManager _roomManager;
    StatisticsManager _statisticsManager;
    GameManager _gameManager;
    IDatabase* _database;
};