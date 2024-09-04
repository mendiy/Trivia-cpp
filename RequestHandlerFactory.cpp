#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) :
    _loginManager(database), _statisticsManager(database), _roomManager()
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
