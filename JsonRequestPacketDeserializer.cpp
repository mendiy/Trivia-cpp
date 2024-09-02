#include "JsonRequestPacketDeserializer.h"

static const int DATA_LEN = 4;

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char>& buffer)
{
	
	//std::string jsonString(buffer.begin(), buffer.end());
	json loginJson = json::parse(buffer);
	//json loginJson = json::from_bson(buffer);
	
	LoginRequest newLogin = { loginJson["username"], loginJson["password"] };
	std::cout << newLogin.username << " " << newLogin.password << "\n";

	return newLogin;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char>& buffer)
{
	return SignupRequest();
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