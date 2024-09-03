#pragma once
#include "IDatabase.h"
#include "sqlite3.h"

class SqliteDataBase : public IDatabase
{
public:
	SqliteDataBase();
	~SqliteDataBase();
	bool open();
	bool close();
	bool doesUserExist(std::string username);
	bool doesPasswordMatch(std::string password, std::string username);
	bool addNewUser(std::string username, std::string password, std::string email);
	sqlite3* db;

	
};