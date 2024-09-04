#include "RoomAdminRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

#define GET_ROOM_ADMIN_STATE_REQUEST 9
#define CLOSE_ROOM_REQUEST 7
#define START_GAME_REQUEST 8

RoomAdminRequestHandler::RoomAdminRequestHandler(LoggedUser user, Room room, RequestHandlerFactory& handlerFactory)
	: _handlerFactory(handlerFactory), _user(user.getUsername()), _room(room)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo reqInfo)
{
	return reqInfo.id == GET_ROOM_ADMIN_STATE_REQUEST
		|| reqInfo.id == CLOSE_ROOM_REQUEST
		|| reqInfo.id == START_GAME_REQUEST;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo reqInfo)
{
	try
	{
		switch (reqInfo.id)
		{
			case(GET_ROOM_ADMIN_STATE_REQUEST):
				return getRoomState(reqInfo);
			case(CLOSE_ROOM_REQUEST):
				return closeRoom(reqInfo);
			case(START_GAME_REQUEST):
				return startGame(reqInfo);
		}
	}
	catch (...)
	{
		ErrorResponse er = { "Error in server db" };
		std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(er);
		return { bufferToSend, nullptr };
	}
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo reqInfo)
{
	int success = _handlerFactory.getRoomManager().deleteRoom(_room.getRoom().id);
	if (success == 0)
	{
		std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse());
		return { bufferToSend, _handlerFactory.createMenuRequestHandler(_user) };
	}
	ErrorResponse er = { "Error in close room" };
	std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(er);
	return { bufferToSend, _handlerFactory.createRoomAdminHandler(_user, _room) };
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo reqInfo)
{
	//TODO call game manager
	std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(StartGameResponse());
	return { bufferToSend, _handlerFactory.createRoomAdminHandler(_user, _room) }; // TODO go to game handler
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo reqInfo)
{
	GetRoomStateResponse roomState;
	// TODO fill room data
	std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(roomState);
	return { bufferToSend, _handlerFactory.createRoomMemberRequestHandler(_user, _room) };
}
