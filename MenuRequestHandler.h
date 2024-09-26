#pragma once
#include "LoggedUser.h"
#include "IRequestHandler.h"
class RequestHandlerFactory;


class MenuRequestHandler : public IRequestHandler
{
public:
    MenuRequestHandler(LoggedUser user, RequestHandlerFactory& handlerFactory);
    virtual bool isRequestRelevant(RequestInfo reqInfo) override;
    virtual RequestResult handleRequest(RequestInfo reqInfo) override;
private:
    LoggedUser _user;
    RequestHandlerFactory& _handlerFactory;
    RequestResult signOut(RequestInfo);
    RequestResult getRooms(RequestInfo);
    RequestResult getPlayersInRoom(RequestInfo);
    RequestResult getPersonalStats(RequestInfo);
    RequestResult getHighScore(RequestInfo);
    RequestResult joinRoom(RequestInfo);
    RequestResult createRoom(RequestInfo);
};