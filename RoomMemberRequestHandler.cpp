#include "RoomMemberRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

#define GET_ROOM_STATE_REQUEST 5
#define LEAVE_ROOM_REQUEST 6

RoomMemberRequestHandler::RoomMemberRequestHandler(LoggedUser user, Room room, RequestHandlerFactory& handlerFactory)
	: _handlerFactory(handlerFactory), _user(user.getUsername()), _room(room)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo reqInfo)
{
	return reqInfo.id == GET_ROOM_STATE_REQUEST || reqInfo.id == LEAVE_ROOM_REQUEST;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo reqInfo)
{
	try
	{
		if (reqInfo.id == GET_ROOM_STATE_REQUEST)
			return getRoomState(reqInfo);
		return leaveRoom(reqInfo);
	}
	catch (...)
	{
			ErrorResponse er = { "Error in server db" };
			std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(er);
			return { bufferToSend, nullptr };
	}
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo reqInfo)
{
	GetRoomStateResponse roomState;
	// TODO fill room data
	std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(roomState);
	return { bufferToSend, _handlerFactory.createRoomMemberRequestHandler(_user, _room) };
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo reqInfo)
{
	int success = _handlerFactory.getRoomManager().getRoom(_room.getRoom().id).removeUser(_user);
	if (success == 0)
	{
		std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse());
		return { bufferToSend, _handlerFactory.createMenuRequestHandler(_user) };
	}
	ErrorResponse er = { "Error in removed" };
	std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(er);
	return { bufferToSend, _handlerFactory.createMenuRequestHandler(_user) };
}
