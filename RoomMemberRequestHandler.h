#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "LoggedUser.h"
#include "RoomManager.h"

class RequestHandlerFactory;

class RoomMemberRequestHandler : public IRequestHandler
{
public:
    RoomMemberRequestHandler(LoggedUser user, Room& room, RequestHandlerFactory& handlerFactory);
    virtual bool IsRequestRelevant(RequestInfo reqInfo) override;
    virtual RequestResult HandleRequest(RequestInfo reqInfo) override;
private:
    Room& _room;
    LoggedUser _user;
    //RoomManager& _roomManager; // from uml but prob a mistake
    RequestHandlerFactory& _handlerFactory;
    RequestResult getRoomState(RequestInfo reqInfo);
    RequestResult leaveRoom(RequestInfo reqInfo);
};
