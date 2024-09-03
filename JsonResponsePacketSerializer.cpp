#include "JsonResponsePacketSerializer.h"
#include "json.hpp"
#include <iostream>

using json = nlohmann::json;

static void serializeJson(const json& j, std::vector<unsigned char>& buffer)
{
    const int DATA_SIZE = 4;
    std::vector<unsigned char> vBson = json::to_bson(j);
    //json test = json::from_bson(vBson);
    //std::cout << test["status"] << "\n";
    unsigned int size = vBson.size();
    std::cout << "len: " << size << "\n";
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
    for (int i = 0; i < vBson.size(); i++)
        buffer.push_back(vBson[i]);
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


