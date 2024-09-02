#pragma comment (lib, "ws2_32.lib")
#include "Server.h"
#include "WSAInitializer.h"
#include <iostream>
#include <fstream>
#include <exception>
#include "JsonResponsePacketSerializer.h"

int main()
{
	try
	{
		// NOTICE at the end of this block the WSA will be closed 
		WSAInitializer wsa_init;
		Server server;
		server.run();
		//std::vector<unsigned char> res = JsonResponsePacketSerializer::serializeResponse(LoginResponse());
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception was thrown in function: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown exception in main !" << std::endl;
	}
}