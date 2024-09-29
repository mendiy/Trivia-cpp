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
    ~Communicator(); 
    void StartHandleRequest();
private:
    void BindAndListen() const;
    void HandleNewClient(SOCKET clientSocket);
    SOCKET m_serverSocket;
    unordered_map<SOCKET, IRequestHandler*> m_clients;
    RequestHandlerFactory& m_handlerFactory;
    std::mutex m_clientsMutex;
};