#pragma comment (lib, "ws2_32.lib")
#include "Server.h"
#include "WSAInitializer.h"
#include <iostream>
#include <fstream>
#include <exception>
#include "JsonResponsePacketSerializer.h"

int main()
{
	IDatabase* db = new IDatabase; // change later
	try
	{
		// NOTICE at the end of this block the WSA will be closed 
		WSAInitializer wsa_init;
		Server server(db);
		server.run();
		delete db;
	}
	catch (const std::exception& e)
	{
		delete db;
		std::cout << "Exception was thrown in function: " << e.what() << std::endl;
	}
	catch (...)
	{
		delete db;
		std::cout << "Unknown exception in main !" << std::endl;
	}
}