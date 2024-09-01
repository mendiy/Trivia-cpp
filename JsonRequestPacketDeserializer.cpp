#include "JsonRequestPacketDeserializer.h"

static const int DATA_LEN = 4;

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char>& buffer)
{
	unsigned char messageLen[DATA_LEN];
	for (int i = 0; i < DATA_LEN; i++)
	{
		messageLen[i] = buffer[i];
	}

	return LoginRequest();
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char>& buffer)
{
	return SignupRequest();
}

int JsonRequestPacketDeserializer::binaryToDecimal(unsigned char* buffer)
{
	return (buffer[3] << 24) + (buffer[2] << 16) + (buffer[1] << 8) + buffer[0];

}