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

int JsonRequestPacketDeserializer::binaryToDecimal(unsigned char* buffer)
{
	//unsigned char messageLen[DATA_LEN];
	//for (int i = 0; i < DATA_LEN; i++)
	//{
	//	messageLen[i] = buffer[i];
	//}

	return (buffer[3] << 24) + (buffer[2] << 16) + (buffer[1] << 8) + buffer[0];

}
