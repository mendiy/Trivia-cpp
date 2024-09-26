#pragma once
#include "IRequestHandler.h"
//#include "RequestHandlerFactory.h"
class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
    LoginRequestHandler(RequestHandlerFactory& handlerFactory);
    virtual bool isRequestRelevant(RequestInfo reqInfo) override;
    virtual RequestResult handleRequest(RequestInfo reqInfo) override;
private:
    RequestHandlerFactory& _handlerFactory;
    RequestResult login(RequestInfo reqInfo);
    RequestResult signup(RequestInfo reqInfo);
};