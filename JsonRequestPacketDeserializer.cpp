#include "JsonRequestPacketDeserializer.h"

static const int DATA_LEN = 4;

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char>& buffer)
{
    

    json loginJson = json::parse(buffer);
    
    LoginRequest newLogin = { loginJson["username"], loginJson["password"] };
    std::cout << newLogin.username << " " << newLogin.password << "\n";

    return newLogin;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char>& buffer)
{
    json signupJson  = json::parse(buffer);
    SignupRequest newSign = { signupJson["username"], signupJson["password"], signupJson["email"]};
    std::cout << newSign.username << " " << newSign.password << newSign.email << "\n";
    return newSign;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayerRequest(std::vector<unsigned char>& buffer)
{
    json reqJson = json::parse(buffer);
    GetPlayersInRoomRequest newReq = { reqJson["roomId"]};
    std::cout << "Get Players in RoomId: " << newReq.roomId << "\n";
    return newReq;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<unsigned char>& buffer)
{
    json reqJson = json::parse(buffer);
    std::cout << "req Join Json: " << reqJson << "\n";
    JoinRoomRequest newReq = { reqJson["roomId"] };
    std::cout << "Join RoomId: " << newReq.roomId << "\n";
    return newReq;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<unsigned char>& buffer)
{
    json reqJson = json::parse(buffer);
    std::cout << "create room json: " << reqJson << "\n";
    CreateRoomRequest newReq = { reqJson["roomName"], reqJson["maxUsers"], reqJson["questionCount"], reqJson["answerTimeout"] };
    std::cout << "Create Room: " << newReq.roomName << "\n";
    return newReq;
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(std::vector<unsigned char>& buffer)
{
    json reqJson = json::parse(buffer);
    std::cout << "submit answer json: " << reqJson << "\n";
    SubmitAnswerRequest newReq = { reqJson["id"]};
    std::cout << "answer id: " << newReq.answerId << "\n";
    return newReq;
}

//int JsonRequestPacketDeserializer::binaryToDecimal(unsigned char* buffer)
//{
//    //unsigned char messageLen[DATA_LEN];
//    //for (int i = 0; i < DATA_LEN; i++)
//    //{
//    //    messageLen[i] = buffer[i];
//    //}
//
//    return (buffer[3] << 24) + (buffer[2] << 16) + (buffer[1] << 8) + buffer[0];
//
//}
