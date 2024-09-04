#include "MenuRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"

#define LOGOUT_REQUEST_CODE 200
#define GET_ROOMS_REQUEST_CODE 201
#define GET_PLAYERS_REQUEST_CODE 202
#define GET_PERSONAL_STATS_REQUEST_CODE 203
#define GET_HIGHSCORE_REQUEST_CODE 204
#define JOIN_ROOM_REQUEST_CODE 205
#define CREATE_ROOM_REQUEST_CODE 206

MenuRequestHandler::MenuRequestHandler(LoggedUser user, RequestHandlerFactory& handlerFactory) : _handlerFactory(handlerFactory) , _user(user.getUsername())
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo reqInfo)
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

RequestResult MenuRequestHandler::handleRequest(RequestInfo reqInfo)
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
        ErrorResponse er = { "Error in server db" };
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
    // call room manager
    GetRoomsResponse gr = { std::vector<RoomData>{} };
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(gr);
    return { bufferToSend, _handlerFactory.createMenuRequestHandler(_user) }; 
    /*int successLogout = _handlerFactory.getLoginManager().logout(_user.getUsername());
    if (successLogout == 0)
    {
        std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(LogoutResponse());
        return { bufferToSend, _handlerFactory.createLoginRequestHandler() };
    }*/
    /*ErrorResponse er = { "Error in getRoom" };
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(er);
    return { bufferToSend, _handlerFactory.createMenuRequestHandler(_user) };*/
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo reqInfo)
{
    GetPlayersInRoomRequest getReq = JsonRequestPacketDeserializer::deserializeGetPlayerRequest(reqInfo.buffer);
    // call room manager
    GetPlayersInRoomResponse getRes = { std::vector<std::string>{} };
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(getRes);
    return { bufferToSend, _handlerFactory.createMenuRequestHandler(_user) };
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo reqInfo)
{
    // call stat manager
    GetPersonalStatsResponse getRes = { std::vector<std::string>{} };
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(getRes);
    return { bufferToSend, _handlerFactory.createMenuRequestHandler(_user) };
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo reqInfo)
{
    // call stat manager
    GetHighScoreResponse getRes = { std::vector<std::string>{} };
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(getRes);
    return { bufferToSend, _handlerFactory.createMenuRequestHandler(_user) };
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo reqInfo)
{
    JoinRoomRequest joinReq = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(reqInfo.buffer);
    // call room manager
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse());
    return { bufferToSend, _handlerFactory.createMenuRequestHandler(_user) }; // next version we need to update handler
}

RequestResult MenuRequestHandler::createRoom(RequestInfo reqInfo)
{
    CreateRoomRequest joinReq = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(reqInfo.buffer);
    // call room manager
    std::vector<unsigned char> bufferToSend = JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse());
    return { bufferToSend, _handlerFactory.createMenuRequestHandler(_user) }; // next version we need to update handler
}
