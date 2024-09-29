#include "MenuRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

#define LOGOUT_REQUEST_CODE 5
#define GET_ROOMS_REQUEST_CODE 7
#define GET_PLAYERS_REQUEST_CODE 11
#define GET_PERSONAL_STATS_REQUEST_CODE 23
#define GET_HIGHSCORE_REQUEST_CODE 19
#define JOIN_ROOM_REQUEST_CODE 13
#define CREATE_ROOM_REQUEST_CODE 17

MenuRequestHandler::MenuRequestHandler(LoggedUser user, RequestHandlerFactory& handlerFactory) 
    : _handlerFactory(handlerFactory) , _user(user.getUsername())
{
}

bool MenuRequestHandler::IsRequestRelevant(RequestInfo reqInfo)
{
    std::cout << ctime(&reqInfo.recievalTime) << "\n";
    return reqInfo.id == LOGOUT_REQUEST_CODE 
        || reqInfo.id == GET_ROOMS_REQUEST_CODE 
        || reqInfo.id == GET_PLAYERS_REQUEST_CODE
        || reqInfo.id == GET_PERSONAL_STATS_REQUEST_CODE
        || reqInfo.id == GET_HIGHSCORE_REQUEST_CODE
        || reqInfo.id == JOIN_ROOM_REQUEST_CODE
        || reqInfo.id == CREATE_ROOM_REQUEST_CODE;
}

RequestResult MenuRequestHandler::HandleRequest(RequestInfo reqInfo)
{
    try
    {
        switch (reqInfo.id)
        {
        case LOGOUT_REQUEST_CODE:
            return signOut(reqInfo);
        case GET_ROOMS_REQUEST_CODE:
            return getRooms(reqInfo);
        case GET_PLAYERS_REQUEST_CODE:
            return getPlayersInRoom(reqInfo);
        case GET_PERSONAL_STATS_REQUEST_CODE:
            return getPersonalStats(reqInfo);
        case GET_HIGHSCORE_REQUEST_CODE:
            return getHighScore(reqInfo);
        case JOIN_ROOM_REQUEST_CODE:
            return joinRoom(reqInfo);
        case CREATE_ROOM_REQUEST_CODE:
            return createRoom(reqInfo);
        }
    }
    catch (...)
    {
        ErrorResponse er = { "Error in server db from menu handler" };
        std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(er);
        return { bufferToSend, nullptr };
    }
}

RequestResult MenuRequestHandler::signOut(RequestInfo reqInfo)
{
    int successLogout = _handlerFactory.getLoginManager().logout(_user.getUsername());
    if (successLogout == 0)
    {
        std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(LogoutResponse());
        return { bufferToSend, _handlerFactory.createLoginRequestHandler() };
    }
    ErrorResponse er = { "Error in logout" };
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(er);
    return { bufferToSend, _handlerFactory.createMenuRequestHandler(_user) };
}

RequestResult MenuRequestHandler::getRooms(RequestInfo reqInfo)
{
    std::vector<RoomData> rooms = _handlerFactory.getRoomManager().getRooms();
    GetRoomsResponse gr = { rooms };
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(gr);
    return { bufferToSend, _handlerFactory.createMenuRequestHandler(_user) }; 
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo reqInfo)
{
    GetPlayersInRoomRequest getReq = JsonRequestPacketDeserializer::deserializeGetPlayerRequest(reqInfo.buffer);
    std::vector<std::string> players = _handlerFactory.getRoomManager().getRoom(getReq.roomId).getAllUsers();
    GetPlayersInRoomResponse getRes = { players };
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(getRes);
    return { bufferToSend, _handlerFactory.createMenuRequestHandler(_user) };
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo reqInfo)
{
    std::vector<std::string> stats = _handlerFactory.getStatisticsManager().getUserStatistics(_user.getUsername());
    GetPersonalStatsResponse getRes = { stats };
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(getRes);
    return { bufferToSend, _handlerFactory.createMenuRequestHandler(_user) };
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo reqInfo)
{
    std::vector<std::string> stats = _handlerFactory.getStatisticsManager().getHighScore();
    GetHighScoreResponse getRes = { stats };
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(getRes);
    return { bufferToSend, _handlerFactory.createMenuRequestHandler(_user) };
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo reqInfo)
{
    JoinRoomRequest joinReq = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(reqInfo.buffer);
    int success = _handlerFactory.getRoomManager().getRoom(joinReq.roomId).addUser(_user.getUsername());
    if (success == 0)
    {
        std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse());
        return { bufferToSend, _handlerFactory.createRoomMemberRequestHandler(_user, _handlerFactory.getRoomManager().getRoom(joinReq.roomId))}; 
    }
    ErrorResponse er = { "Error in join room" };
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(er);
    return { bufferToSend, _handlerFactory.createMenuRequestHandler(_user) };
}

RequestResult MenuRequestHandler::createRoom(RequestInfo reqInfo)
{
    CreateRoomRequest createReq = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(reqInfo.buffer);
    RoomData room;
    room.maxPlayers = createReq.maxUsers;
    room.name = createReq.roomName;
    room.numOfQuestionsInGame = createReq.questionCount;
    room.timePerQuestion = createReq.answerTimeout;
    int roomId = _handlerFactory.getRoomManager().createRoom(_user, room);
    if (roomId > 0)
    {
        std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse());
        return { bufferToSend, _handlerFactory.createRoomAdminHandler(_user, _handlerFactory.getRoomManager().getRoom(roomId)) };
    }
    ErrorResponse er = { "Error in create room" };
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(er);
    return { bufferToSend, _handlerFactory.createMenuRequestHandler(_user) };
}
