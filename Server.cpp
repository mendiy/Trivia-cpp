#include "Server.h"
#include <thread>
#include <string>
#include <iostream>

Server::Server()
{
	_communicator = new Communicator;
}

Server::~Server()
{
	delete _communicator;
}

void Server::run()
{
	std::thread communicatorThread(&Communicator::startHandleRequest, this->_communicator);
	communicatorThread.detach();

	std::string adminInput = "";
	while (adminInput != "exit")
	{
		std::cout << "enter exit to close server.\n";
		std::cin >> adminInput;
	}
}
