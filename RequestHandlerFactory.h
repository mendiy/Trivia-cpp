#pragma once
#include "LoginRequestHandler.h"

// for test
class LoginManager
{

};
// for test
class IDatabase
{

};

// for test
class MenuRequestHandler : public IRequestHandler
{

};

// for test
class MenuManager
{

};

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(); // for now, need to fix next version
	LoginManager& getLoginManager();
private:
	LoginManager _loginManager;
	IDatabase* _database;
};