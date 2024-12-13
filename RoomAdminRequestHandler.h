#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "LoggedUser.h"
#include "RoomManager.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(LoggedUser user, Room room, RequestHandlerFactory& handlerFactory);
	virtual bool isRequestRelevant(RequestInfo reqInfo) override;
	virtual RequestResult handleRequest(RequestInfo reqInfo) override;
private:
	Room _room;
	LoggedUser _user;
	//RoomManager& _roomManager; // from uml but prob a mistake
	RequestHandlerFactory& _handlerFactory;
	RequestResult closeRoom(RequestInfo reqInfo);
	RequestResult startGame(RequestInfo reqInfo);
	RequestResult getRoomState(RequestInfo reqInfo);
};
