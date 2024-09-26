#pragma once
#include "Communicator.h"
#include "RequestHandlerFactory.h"

class IDatabase;

class Server
{
public:
    Server(IDatabase* database);
    ~Server();
    void run();
private:
    IDatabase* _database;
    RequestHandlerFactory _handlerFactory;
    Communicator* _communicator;
};