
#include <iostream>
#include <vector>
#include "json.hpp"

// for convenience
using json = nlohmann::json;

struct SubmitAnswerRequest
{
	unsigned int answerId;
};

struct GetPlayersInRoomRequest
{
	unsigned int roomId;
};

struct JoinRoomRequest
{
	unsigned int roomId;
};

struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

struct LoginRequest
{
	std::string username;
	std::string password;
}; 

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
	static GetPlayersInRoomRequest deserializeGetPlayerRequest(std::vector<unsigned char>& buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(std::vector<unsigned char>& buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(std::vector<unsigned char>& buffer);
	static SubmitAnswerRequest deserializeSubmitAnswerRequest(std::vector<unsigned char>& buffer);
private:
	//static int binaryToDecimal(unsigned char* buffer);


};
