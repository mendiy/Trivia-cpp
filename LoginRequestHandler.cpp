#include "LoginRequestHandler.h"
#include <iostream>
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

#define LOGIN_REQUEST_CODE 111
#define SIGNUP_REQUEST_CODE 112

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory) : _handlerFactory(handlerFactory)
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo reqInfo)
{
    std::cout << ctime(&reqInfo.recievalTime) << "\n";
    return reqInfo.id == LOGIN_REQUEST_CODE || reqInfo.id == SIGNUP_REQUEST_CODE;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo reqInfo)
{
    try
    {
        if (reqInfo.id == LOGIN_REQUEST_CODE)
            return login(reqInfo);
        return signup(reqInfo);
    }
    catch (...)
    {
        ErrorResponse er = { "Error in server db" };
        std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(er);
        return { bufferToSend, nullptr };
    }
}

RequestResult LoginRequestHandler::login(RequestInfo reqInfo)
{
    LoginRequest lr = JsonRequestPacketDeserializer::deserializeLoginRequest(reqInfo.buffer);
    std::cout << lr.username << ", " << lr.password << "\n";
    // call login manager
    int successLogin = _handlerFactory.getLoginManager().login(lr.username, lr.password);
    if (successLogin == 0)
    {
        std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(LoginResponse());
        return { bufferToSend, _handlerFactory.createMenuRequestHandler() };
    }

    ErrorResponse er = { "Error in login details" };
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(er);
    return { bufferToSend, _handlerFactory.createLoginRequestHandler()};
}

RequestResult LoginRequestHandler::signup(RequestInfo reqInfo)
{
    SignupRequest sr = JsonRequestPacketDeserializer::deserializeSignupRequest(reqInfo.buffer);
    // call login manager
    int successSignup = _handlerFactory.getLoginManager().signup(sr.username, sr.password, sr.email);
    if (successSignup == 0)
    {
        std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(SignUpResponse());
        return { bufferToSend, _handlerFactory.createMenuRequestHandler() };
    }

    ErrorResponse er = { "Error in signup details" };
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(er);
    return { bufferToSend, _handlerFactory.createLoginRequestHandler() };
}
