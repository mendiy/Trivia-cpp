#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <unordered_map>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include <mutex>

using std::unordered_map;

class Communicator
{
public:
    Communicator(RequestHandlerFactory& handlerFactory);
    ~Communicator(); // need to clean the map 
    void startHandleRequest();
private:
    void bindAndListen() const;
    void handleNewClient(SOCKET clientSocket);
    SOCKET _serverSocket;
    unordered_map<SOCKET, IRequestHandler*> _clients;
    RequestHandlerFactory& _handlerFactory;
    std::mutex _clientsMutex;
};