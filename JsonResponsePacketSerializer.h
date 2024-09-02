#pragma once
#include <vector>


struct ErrorResponse
{
	unsigned int status { 255 };
};

struct LoginResponse
{
	unsigned int status { 100 };
}; 

struct SignUpResponse
{
	unsigned int status { 101 };
};

class JsonResponsePacketSerializer
{
public:
	static std::vector<unsigned char> serializeResponse(ErrorResponse);
	static std::vector<unsigned char> serializeResponse(LoginResponse);
	static std::vector<unsigned char> serializeResponse(SignUpResponse);
//private:
	//static void serializeJson(const json& j, std::vector<unsigned char>& buffer);
};