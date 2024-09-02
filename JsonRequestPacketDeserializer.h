#include "JsonRequestPacketDeserializer.h"

static const int DATA_LEN = 4;

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char>& buffer)
{

	json loginJson = json::from_bson(buffer);

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
 31 changes: 31 additions & 0 deletions31  
trivia/trivia/JsonRequestPacketDeserializer.h
Viewed
Original file line number	Diff line number	Diff line change
@@ -0,0 +1,31 @@
#include <iostream>
#include <vector>
#include "json.hpp"

// for convenience
using json = nlohmann::json;

struct LoginRequest
{
	std::string username;
	std::string password;
}; LoginRequest;

struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;

};

class JsonRequestPacketDeserializer
{
	public:
		static LoginRequest deserializeLoginRequest(std::vector<unsigned char>& buffer);
		static SignupRequest deserializeSignupRequest(std::vector<unsigned char>& buffer);
	private:
		static int binaryToDecimal(unsigned char* buffer);


}
