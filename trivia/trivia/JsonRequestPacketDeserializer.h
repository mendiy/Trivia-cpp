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


};