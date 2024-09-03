#pragma once
#include <iostream>

class IDatabase
{
public: 
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual bool doesUserExist(std::string) = 0;
	virtual bool doesPasswordMatch(std::string, std::string) = 0;
	virtual bool addNewUser(std::string, std::string, std::string) = 0;
};