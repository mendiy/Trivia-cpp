#include "JsonResponsePacketSerializer.h"
#include "json.hpp"
#include <iostream>

using json = nlohmann::json;

static void serializeJson(const json& j, std::vector<unsigned char>& buffer)
{
    const int DATA_SIZE = 4;
    std::string Jstr = j.dump();
    unsigned int JstrSize = Jstr.size();
    std::cout << "len: " << JstrSize << "\n";
    unsigned char sizeChar[DATA_SIZE]{};
    for (int i = DATA_SIZE - 1; i >= 0; i--)
    {
        sizeChar[i] = JstrSize;
        JstrSize = JstrSize >> 8;
    }
    for (int i = 0; i < DATA_SIZE; i++)
    {
        buffer.push_back(sizeChar[i]);
    }
    for (int i = 0; i < Jstr.size(); i++)
        buffer.push_back(Jstr[i]);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse er)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(er.status);
    json j;
    j["message"] = er.message;
    serializeJson(j, buffer);
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse lr)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(lr.status);
    json j;
    //json j = R"({"status": 100})"_json;
    j["status"] = lr.status;
    serializeJson(j, buffer);
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignUpResponse sr)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(sr.status);
    json j;
    j["status"] = sr.status;
    serializeJson(j, buffer);
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LogoutResponse lr)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(lr.status);
    json j;
    j["status"] = lr.status;
    serializeJson(j, buffer);
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse gr)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(gr.status);
    json j;
    j["Rooms"] = json::array();
    for (RoomData rd : gr.rooms)
    {
        json temp = { 
            {"roomId", rd.id}, 
            {"maxPlayers", rd.maxPlayers}, 
            {"qTimeout", rd.timePerQuestion},
            {"isActive", rd.isActive},
            {"roomName", rd.name},
            {"numOfQuestions", rd.numOfQuestionsInGame}
        }; 
        j["Rooms"].push_back(temp);
    }
    serializeJson(j, buffer);
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse gp)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(gp.status);
    json j;
    j["PlayersInRooms"] = json::array();
    for (std::string player : gp.players)
    {
        j["PlayersInRooms"].push_back(player);
    }
    serializeJson(j, buffer);
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse jr)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(jr.status);
    json j;
    j["status"] = jr.status;
    serializeJson(j, buffer);
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse cr)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(cr.status);
    json j;
    j["status"] = cr.status;
    serializeJson(j, buffer);
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetHighScoreResponse gh)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(gh.status);
    json j;
    j["HighScores"] = json::array();
    for (std::string highScore : gh.highScores)
    {
        j["HighScores"].push_back(highScore);
    }
    serializeJson(j, buffer);
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetPersonalStatsResponse gs)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(gs.status);
    json j;
    j["UserStatistics"] = json::array();
    for (std::string stat : gs.statistics)
    {
        j["UserStatistics"].push_back(stat);
    }
    serializeJson(j, buffer);
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse cr)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(cr.status);
    json j;
    j["status"] = cr.status;
    serializeJson(j, buffer);
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(StartGameResponse sg)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(sg.status);
    json j;
    j["status"] = sg.status;
    serializeJson(j, buffer);
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse gr)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(gr.status);
    json j = {
        {"status", gr.status},
        {"hasGameBegun", gr.hasGameBegun},
        {"AnswerCount", gr.questionCount},
        {"answerTimeOut", gr.answerTimeout}
    };
    j["players"] = json::array();
    for (auto player : gr.players)
        j["players"].push_back(player);
    serializeJson(j, buffer);
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse lr)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(lr.status);
    json j;
    j["status"] = lr.status;
    serializeJson(j, buffer);
    return buffer;
}


