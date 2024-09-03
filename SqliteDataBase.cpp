#include "SqliteDataBase.h"

SqliteDataBase::SqliteDataBase()
{
}

SqliteDataBase::~SqliteDataBase()
{
}

bool SqliteDataBase::open()
{
	return false;
}

bool SqliteDataBase::close()
{
	return false;
}

int SqliteDataBase::doesUserExist(std::string) const
{
	return 0;
}

int SqliteDataBase::doesPasswordMatch(std::string, std::string) const
{
	return 0;
}

int SqliteDataBase::addNewUser(std::string, std::string, std::string)
{
	return 0;
}
