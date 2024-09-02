#include "JsonRequestPacketDeserializer.h"

static const int DATA_LEN = 4;

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char>& buffer)
{
	std::cout << buffer.data() << "\n";
	std::string jsonString(buffer.begin(), buffer.end());
	json loginJson = json::parse(jsonString);
	//json loginJson = json::from_bson(buffer);
	LoginRequest newLogin = { loginJson["username"], loginJson["password"] };
	std::cout << newLogin.username << " " << newLogin.password << "\n";

	return newLogin;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char>& buffer)
{
	std::cout << buffer.data() << "\n";

	std::string jsonString(buffer.begin(), buffer.end());
	json signupJson  = json::parse(jsonString);
	//json signupJson = json::from_bson(buffer);
	SignupRequest newSign = { signupJson["username"], signupJson["password"], signupJson["email"]};
	std::cout << newSign.username << " " << newSign.password << newSign.email << "\n";
	return newSign;
}

int JsonRequestPacketDeserializer::binaryToDecimal(unsigned char* buffer)
{

	return (buffer[3] << 24) + (buffer[2] << 16) + (buffer[1] << 8) + buffer[0];

}
