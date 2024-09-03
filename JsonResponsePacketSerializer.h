#pragma once
#include <vector>
#include <string>

#define ERROR_RESPONSE_CODE 255
#define LOGIN_RESPONSE_CODE 100
#define SIGNUP_RESPONSE_CODE 101

struct ErrorResponse
{
	std::string message{ };
	unsigned int status { ERROR_RESPONSE_CODE };
};

struct LoginResponse
{
	unsigned int status { LOGIN_RESPONSE_CODE };
}; 

struct SignUpResponse
{
	unsigned int status { SIGNUP_RESPONSE_CODE };
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