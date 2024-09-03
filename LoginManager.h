#pragma once
#include <iostream>
#include <vector>
#include "IDatabase.h"
#include "LoggedUser.h"

class LoginManager
{
	public:
		void signup(std::string, std::string, std::string);
		void login(std::string, std::string);
		void logout(std::string username);
	private:
		IDatabase * m_database;
		std::vector<LoggedUser> m_loggedUsers;
};
