#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : _loginManager(database)
{
    _database = database;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return new LoginRequestHandler(*this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler()
{
    return new MenuRequestHandler();
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return _loginManager;
}
