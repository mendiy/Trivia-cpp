#pragma once
#include "IDatabase.h"

class SqliteDataBase : public IDatabase
{
public:
	SqliteDataBase();
	~SqliteDataBase();
	bool open();
	bool close();
	int doesUserExist(std::string) const;
	int doesPasswordMatch(std::string, std::string) const;
	int addNewUser(std::string, std::string, std::string);
};