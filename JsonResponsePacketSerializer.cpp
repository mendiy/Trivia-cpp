#include "JsonResponsePacketSerializer.h"
#include "json.hpp"

using json = nlohmann::json;

static void serializeJson(const json& j, std::vector<unsigned char>& buffer)
{
    const int DATA_SIZE = 4;
    std::vector<unsigned char> vBson = json::to_bson(j);
    unsigned int size = vBson.size();
    unsigned char sizeChar[DATA_SIZE]{};
    for (int i = DATA_SIZE - 1; i >= 0; i--)
    {
        sizeChar[i] = size;
        size = size >> 8;
    }
    for (int i = 0; i < DATA_SIZE; i++)
    {
        buffer.push_back(sizeChar[i]);
    }
    for (auto it = vBson.begin(); it != vBson.end(); it++)
        buffer.push_back(*it);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse er)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(er.status);
    json j = { "message", "ERROR"};
    serializeJson(j, buffer);
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse lr)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(lr.status);
    json j = {"status", lr.status};
    serializeJson(j, buffer);
    return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignUpResponse sr)
{
    std::vector<unsigned char> buffer;
    buffer.push_back(sr.status);
    json j = { "status", sr.status };
    serializeJson(j, buffer);
    return buffer;
}


