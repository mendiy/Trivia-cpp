#pragma once
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "LoginManager.h"


// for test
class MenuRequestHandler : public IRequestHandler
{
	virtual bool isRequestRelevant(RequestInfo reqInfo) { return false; };
	virtual RequestResult handleRequest(RequestInfo reqInfo) { return {}; };
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