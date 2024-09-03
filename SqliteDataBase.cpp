#include "SqliteDataBase.h"
#include <exception>
#include <iostream>
#include <string>
#include "sqlite3.h"
#include "LoggedUser.h"
#include "IDatabase.h"
#include <io.h>

//static std::string user;

static int callback(void* isExists, int argc, char** argv, char** azColName) {
	int i;
	if (argc > 0 && argv[0])
	{
		*(bool*)isExists = (*argv[0] == '1');
	}

	
	//for (i = 0; i < argc; i++) {
	//	printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	//	/*if (std::string(azColName[i]) == "USERNAME" && strcmp(argv[i], username) == true){
	//		user = argv[i];
	//	}*/
	//	
	

	return 0;
}

SqliteDataBase::SqliteDataBase()
{
	db = nullptr;

	if (open() == false)
	{
		throw "Failed to open DB";
	}
	std::string userTable = "CREATE TABLE IF NOT EXISTS USERS ("
		"USERNAME TEXT NOT NULL PRIMARY KEY,"
		"PASSWORD TEXT NOT NULL,"
		"EMAIL TEXT NOT NULL); ";
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, userTable.c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
		std::cout << "Failed to open User Table\n";

	std::cout << "DB Created!" << std::endl;
}

SqliteDataBase::~SqliteDataBase()
{
	
}

bool SqliteDataBase::open()
{

	std::string dbFileName = "Trivia_DB";
	int res = sqlite3_open(dbFileName.c_str(), &db);
	if (res != SQLITE_OK)
	{
		db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return false;
	}
	return true;
}

bool SqliteDataBase::close()
{
	return false;
}

bool SqliteDataBase::doesUserExist(std::string username)
{
	char* zErrMsg = 0;
	bool isExists = false;
	std::string sql = "SELECT EXISTS(SELECT 1 from USERS WHER USERNAME = '" + username + "');";

	/* Execute SQL statement */
	int rc = sqlite3_exec(db, sql.c_str(), nullptr, &isExists, &zErrMsg);

	if (rc != SQLITE_OK) {
		std::cerr << zErrMsg << "\n";
		sqlite3_free(zErrMsg);
		return false;
	}
	
	std::cout << "user selected\n";
	
	sqlite3_close(db);
	
	return isExists;
}

bool SqliteDataBase::doesPasswordMatch(std::string username, std::string password)
{
	char* zErrMsg = 0;
	bool isMatch = false;
	std::string sql = "SELECT EXISTS(SELECT 1 from USERS WHERE USERNAME = '" + username + "' AND PASSWORD = '" + password + "');";

	/* Execute SQL statement */
	int rc = sqlite3_exec(db, sql.c_str(), callback, &isMatch, &zErrMsg);

	if (rc != SQLITE_OK) {
		std::cerr << zErrMsg << "\n";
		sqlite3_free(zErrMsg);
		return false;
	}

	std::cout << "password match!\t" << isMatch << "\n";

	sqlite3_close(db);

	return isMatch;
}

bool SqliteDataBase::addNewUser(std::string username, std::string password, std::string email)
{
	char* zErrMsg = 0;
	std::cout << "from add new user: " << username << ", " << password << ", " << email << "\n";
	std::string sql = "INSERT INTO USERS (USERNAME, PASSWORD, EMAIL) "  \
		"VALUES ('" + username + "', '" + password + "', '" + email + "'); ";
	std::cout << "query: " << sql << "\n";
	/* Execute SQL statement */
	int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &zErrMsg);

	if (rc != SQLITE_OK) {
		std::cerr << zErrMsg << "\n";
		sqlite3_free(zErrMsg);
		return false;
	}
	
	std::cout << "user created successfully\n";
	
	sqlite3_close(db);
	return true;
}
