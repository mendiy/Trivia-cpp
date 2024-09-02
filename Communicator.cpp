#include "Communicator.h"
#include <WinSock2.h>
#include <Windows.h>
#include <algorithm>
#include <thread>
#include <iostream>
#include <string>
#include <exception>
#include "Helper.h"
#include <exception>


static const unsigned short PORT = 8000;

Communicator::Communicator() : _clients()
{
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Communicator::~Communicator()
{
	try
	{
		closesocket(_serverSocket);
		std::for_each(_clients.begin(), _clients.end(), [](auto& pair) { delete pair.second; });	
	}
	catch(...)
	{ }
}

void Communicator::startHandleRequest()
{
	
	bindAndListen();

	while (true)
	{
		SOCKET client_socket = accept(_serverSocket, NULL, NULL);
		if (client_socket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);

		// create new thread for client	and detach from it
		std::thread clientThread(&Communicator::handleNewClient, this, client_socket);
		clientThread.detach();
	}
}

void Communicator::bindAndListen() const
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = 0;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << PORT << std::endl;
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	try
	{
		std::string msg = Helper::getStringPartFromSocket(clientSocket, 5);
		std::cout << msg << "\n";
		Helper::sendData(clientSocket, msg);
	}
	catch (const std::exception& e)
	{
		std::cout << "error on client thread:\t" << e.what() << "\n";
		_clients.erase(clientSocket);
		closesocket(clientSocket);
	}
}
