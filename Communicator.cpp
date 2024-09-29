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

Communicator::Communicator(RequestHandlerFactory& handlerFactory) : m_clients(), m_handlerFactory(handlerFactory)
{
    m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (m_serverSocket == INVALID_SOCKET)
        throw std::exception(__FUNCTION__ " - socket");
}


Communicator::~Communicator()
{
    try
    {
        closesocket(m_serverSocket);
        std::for_each(m_clients.begin(), m_clients.end(), [](auto& pair) { delete pair.second; });
    }
    catch (...)
    {
    }
}

void Communicator::StartHandleRequest()
{

    BindAndListen();

    while (true)
    {
        SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
        if (client_socket == INVALID_SOCKET)
            throw std::exception(__FUNCTION__);

        std::cout << "new connection\n";

        // we need to add client to clients map
        std::lock_guard<std::mutex> lock(m_clientsMutex);
        m_clients[client_socket] = m_handlerFactory.createLoginRequestHandler();

        // create new thread for client    and detach from it

        std::thread clientThread(&Communicator::HandleNewClient, this, client_socket);
        clientThread.detach();
    }
}

void Communicator::BindAndListen() const
{
    struct sockaddr_in sa = { 0 };

    sa.sin_port = htons(PORT); // port that server will listen for
    sa.sin_family = AF_INET;   // must be AF_INET
    sa.sin_addr.s_addr = 0;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

    // Connects between the socket and the configuration (port and etc..)
    if (bind(m_serverSocket, (struct sockaddr*) &sa, sizeof(sa)) == SOCKET_ERROR)
        throw std::exception(__FUNCTION__ " - bind");

    // Start listening for incoming requests of clients
    if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
        throw std::exception(__FUNCTION__ " - listen");
    std::cout << "Listening on port " << PORT << std::endl;
}

void Communicator::HandleNewClient(SOCKET clientSocket)
{
    try
    {
        const int HEADER_LENGTH = 5;
        while (true)
        {
            IRequestHandler* currentHandler = m_clients[clientSocket];
            char* header = new char[HEADER_LENGTH];
            int res;
            res = recv(clientSocket, header, HEADER_LENGTH, NULL);
            if (res == SOCKET_ERROR)
            {
                delete[] header;
                std::string s = "-1 Error while recieving from socket: ";
                s += std::to_string(clientSocket);
                s += ". ";
                s += std::to_string(WSAGetLastError());
                throw std::exception(s.c_str());
            }
            
            if (res == 0)
            {
                delete[] header;
                std::cout << "connection closed\n";
                m_clients.erase(clientSocket);
                closesocket(clientSocket);
                return;
            }
            unsigned char code = header[0];
            std::cout << "code req: " << (unsigned int) code << "\n";
            unsigned int jsonSize = 0;
            for (int i = 1; i < HEADER_LENGTH; i++)
            {
                jsonSize = jsonSize << 8;
                jsonSize = jsonSize ^ header[i];
            }
            std::cout << "req len: " << jsonSize << "\n";
            delete[] header;
            std::vector<unsigned char> buffer;
            char* data = new char[jsonSize];
            recv(clientSocket, data, jsonSize, 0);
            if (res == INVALID_SOCKET)
            {
                std::string s = "Error while recieving from socket: ";
                s += std::to_string(clientSocket);
                throw std::exception(s.c_str());
            }

            for (int i = 0; i < jsonSize; i++)
            {
                buffer.push_back(data[i]);
            }
            std::cout << "buffer: " << buffer.data() << "\n";
            delete[] data;
            time_t timestamp;
            RequestInfo reqInfo = { code, time(&timestamp), buffer };
            if (currentHandler->IsRequestRelevant(reqInfo))
            {
                RequestResult reqRes = currentHandler->HandleRequest(reqInfo);
                if (!reqRes.newHandler)
                    throw(std::exception("error in server db")); // throw or remain in same state
                delete currentHandler;
                std::unique_lock<std::mutex> lock(m_clientsMutex);
                m_clients[clientSocket] = reqRes.newHandler;
                lock.unlock();
                int resSize = reqRes.response.size();
                char* response = new char[resSize];
                for (int i = 0; i < resSize; i++)
                {
                    response[i] = reqRes.response[i];
                }
                res = send(clientSocket, response, resSize, 0);
                if (res == INVALID_SOCKET)
                {
                    std::string s = "Error while sending message to client socket: ";
                    s += std::to_string(clientSocket);
                    throw std::exception(s.c_str());
                }
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
        m_clients.erase(clientSocket);
        closesocket(clientSocket);
    }
}
