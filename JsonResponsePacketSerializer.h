#pragma once
#include <vector>
#include <string>
#include "Room.h"

#define ERROR_RESPONSE_CODE 126
#define LOGIN_RESPONSE_CODE 100
#define SIGNUP_RESPONSE_CODE 101
#define LOGOUT_RESPONSE_CODE 101
#define GET_ROOMS_RESPONSE_CODE 20
#define GET_PLAYERS_IN_ROOM_RESPONSE_CODE 30
#define GET_HIGH_SCORE_RESPONSE_CODE 40
#define GET_PERSONAL_STATS_RESPONSE_CODE 50
#define JOIN_ROOM_RESPONSE_CODE 60
#define CREATE_ROOM_RESPONSE_CODE 70
#define CLOSE_RESPONSE_CODE 80
#define START_GAME_RESPONSE_CODE 90
#define GET_ROOM_STATE_RESPONSE_CODE 95
#define LEAVE_ROOM_RESPONSE_CODE 99



struct CloseRoomResponse
{
	unsigned int status{ CLOSE_RESPONSE_CODE };
}; 

struct StartGameResponse
{
	unsigned int status{ START_GAME_RESPONSE_CODE };
}; 

struct GetRoomStateResponse
{
	std::vector<std::string> players{};
	unsigned int answerTimeout{ 0 };
	unsigned int questionCount{ 0 };
	bool hasGameBegun{ false };
	unsigned int status{ GET_ROOM_STATE_RESPONSE_CODE };
};

struct LeaveRoomResponse
{
	unsigned int status{ LEAVE_ROOM_RESPONSE_CODE };
};


struct LogoutResponse
{
	unsigned int status{ LOGOUT_RESPONSE_CODE };
};

struct JoinRoomResponse
{
	unsigned int status{ JOIN_ROOM_RESPONSE_CODE };
};

struct CreateRoomResponse
{
	unsigned int status{ CREATE_ROOM_RESPONSE_CODE };
};

struct GetRoomsResponse
{
	std::vector<RoomData> rooms{};
	unsigned int status{ GET_ROOMS_RESPONSE_CODE };
};

struct GetPlayersInRoomResponse
{
	std::vector<std::string> players{};
	unsigned int status{ GET_PLAYERS_IN_ROOM_RESPONSE_CODE };
};

struct GetHighScoreResponse
{
	std::vector<std::string> highScores{};
	unsigned int status{ GET_HIGH_SCORE_RESPONSE_CODE };
};

struct GetPersonalStatsResponse
{
	std::vector<std::string> statistics{};
	unsigned int status{ GET_PERSONAL_STATS_RESPONSE_CODE };
};

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

	static std::vector<unsigned char> serializeResponse(LogoutResponse);
	static std::vector<unsigned char> serializeResponse(GetRoomsResponse);
	static std::vector<unsigned char> serializeResponse(GetPlayersInRoomResponse);
	static std::vector<unsigned char> serializeResponse(JoinRoomResponse);
	static std::vector<unsigned char> serializeResponse(CreateRoomResponse);
	static std::vector<unsigned char> serializeResponse(GetHighScoreResponse);
	static std::vector<unsigned char> serializeResponse(GetPersonalStatsResponse);

	static std::vector<unsigned char> serializeResponse(CloseRoomResponse);
	static std::vector<unsigned char> serializeResponse(StartGameResponse);
	static std::vector<unsigned char> serializeResponse(GetRoomStateResponse);
	static std::vector<unsigned char> serializeResponse(LeaveRoomResponse);
//private:
	//static void serializeJson(const json& j, std::vector<unsigned char>& buffer);
};