#include "Server.h"
#include <thread>
#include <string>
#include <iostream>

Server::Server(IDatabase* database) : _handlerFactory(database), _communicator(new Communicator(_handlerFactory))
{
    _database = database;
}

Server::~Server()
{
    delete _communicator;
}

void Server::run()
{
    std::thread communicatorThread(&Communicator::StartHandleRequest, this->_communicator);
    communicatorThread.detach();

    std::string adminInput = "";
    while (adminInput != "exit")
    {
        std::cout << "enter exit to close server.\n";
        std::cin >> adminInput;
    }
}
