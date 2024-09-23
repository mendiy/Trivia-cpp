#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) :
    _loginManager(database), _statisticsManager(database), _roomManager() , _gameManager(database)
{
    _database = database;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return new LoginRequestHandler(*this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
    return new MenuRequestHandler(user, *this);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminHandler(LoggedUser user, Room room)
{
    return new RoomAdminRequestHandler(user, room, *this);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser user, Room room)
{
    return new RoomMemberRequestHandler(user, room, *this);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(LoggedUser user, Game game) // TODO check how to get game
{
    return new GameRequestHandler(user, game, *this);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return _loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
    return _roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
    return _statisticsManager;
}

GameManager& RequestHandlerFactory::getGameManager()
{
    return _gameManager;
}
