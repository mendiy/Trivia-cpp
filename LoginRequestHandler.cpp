#include "LoginRequestHandler.h"
#include <iostream>
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory) : _handlerFactory(handlerFactory)
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo reqInfo)
{
    std::cout << ctime(&reqInfo.recievalTime) << "\n";
    return reqInfo.id == 111 || reqInfo.id == 112;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo reqInfo)
{
    try
    {
        if (reqInfo.id == 111)
            return login(reqInfo);
        return signup(reqInfo);
    }
    catch (...)
    {
        std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(ErrorResponse());
        return { bufferToSend, nullptr };
    }
}

RequestResult LoginRequestHandler::login(RequestInfo reqInfo)
{
    LoginRequest lr = JsonRequestPacketDeserializer::deserializeLoginRequest(reqInfo.buffer);
    std::cout << lr.username << ", " << lr.password << "\n";
    // call login manager
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(LoginResponse());
    return { bufferToSend, _handlerFactory.createMenuRequestHandler() };
}

RequestResult LoginRequestHandler::signup(RequestInfo reqInfo)
{
    SignupRequest sr = JsonRequestPacketDeserializer::deserializeSignupRequest(reqInfo.buffer);
    // call login manager
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(SignUpResponse());
    return { bufferToSend, _handlerFactory.createMenuRequestHandler() };
}
