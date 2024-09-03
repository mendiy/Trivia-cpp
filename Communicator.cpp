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
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "LoginRequestHandler.h";
#include "IRequestHandler.h";
#include <ctime>

static const unsigned short PORT = 8000;

Communicator::Communicator(RequestHandlerFactory& handlerFactory) : _clients() , _handlerFactory(handlerFactory)
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

		// we need to add client to clients map
		_clients[client_socket] = _handlerFactory.createLoginRequestHandler();

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
		const int HEADER_LENGTH = 5;
		while (true)
		{
			IRequestHandler* currentHandler = _clients[clientSocket];
			char* header = new char[HEADER_LENGTH];
			recv(clientSocket, header, HEADER_LENGTH, 0);
			unsigned char code = header[0];
			std::cout << code << "\n";
			unsigned int jsonSize = 0;
			for (int i = 1; i < HEADER_LENGTH; i++)
			{
				jsonSize = jsonSize << 8;
				jsonSize = jsonSize ^ header[i];
			}
			std::cout << jsonSize << "\n";
			delete[] header;
			std::vector<unsigned char> buffer;
			char* data = new char[jsonSize];
			recv(clientSocket, data, jsonSize, 0);
			for (int i = 0; i < jsonSize; i++)
			{
				buffer.push_back(data[i]);
			}
			std::cout << buffer.size() << "\n";
			delete[] data;
			time_t timestamp;
			RequestInfo reqInfo = { code, time(&timestamp), buffer};
			if (currentHandler->isRequestRelevant(reqInfo))
			{
				RequestResult reqRes = currentHandler->handleRequest(reqInfo);
				if (!reqRes.newHandler)
					throw(std::exception("error in server db"));
				delete currentHandler;
				_clients[clientSocket] = reqRes.newHandler;
				int resSize = reqRes.response.size();
				char* response = new char[resSize];
				for (int i = 0; i < resSize; i++)
				{
					response[i] = reqRes.response[i];
				}
				send(clientSocket, response, resSize, 0);
				delete[] response;
			}
			else
			{
				std::cout << "wrong login code";
				ErrorResponse er = { "Error in login code" };
				std::vector<unsigned char> responseBuffer = JsonResponsePacketSerializer::serializeResponse(er);
				int resSize = responseBuffer.size();
				char* response = new char[resSize];
				for (int i = 0; i < resSize; i++)
				{
					response[i] = responseBuffer[i];
				}
				send(clientSocket, response, resSize, 0);
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "error on client thread:\t" << e.what() << "\n";
		_clients.erase(clientSocket);
		closesocket(clientSocket);
	}
}
