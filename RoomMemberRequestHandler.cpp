#include "RoomMemberRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"
#include "Room.h"

#define GET_ROOM_STATE_REQUEST 5
#define LEAVE_ROOM_REQUEST 6

RoomMemberRequestHandler::RoomMemberRequestHandler(LoggedUser user, Room& room, RequestHandlerFactory& handlerFactory)
    : _handlerFactory(handlerFactory), _user(user.getUsername()), _room(room)
{
}

bool RoomMemberRequestHandler::IsRequestRelevant(RequestInfo reqInfo)
{
    return reqInfo.id == GET_ROOM_STATE_REQUEST || reqInfo.id == LEAVE_ROOM_REQUEST;
}

RequestResult RoomMemberRequestHandler::HandleRequest(RequestInfo reqInfo)
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
    // TODO repeated code in admin handler and member handler
    GetRoomStateResponse roomState;
    Room currentRoom = _handlerFactory.getRoomManager().getRoom(reqInfo.id);
    RoomData currentRoomData = currentRoom.getRoom();
    roomState.answerTimeout = currentRoomData.timePerQuestion;
    roomState.questionCount = currentRoomData.numOfQuestionsInGame;
    roomState.hasGameBegun = currentRoomData.isActive;
    roomState.players = currentRoom.getAllUsers();
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(roomState);
    if (roomState.hasGameBegun)
        return { bufferToSend, _handlerFactory.createGameRequestHandler(_user, _handlerFactory.getGameManager().getGame(currentRoom.getRoom().id)) };
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
