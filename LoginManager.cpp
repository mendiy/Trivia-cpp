#include "LoginManager.h"
#include <algorithm>

int LoginManager::signup(std::string username, std::string password, std::string email)
{

	bool logged = m_database->addNewUser(username, password, email);
	if (logged)
	{
		LoggedUser loggedUser(username);
		m_loggedUsers.push_back(loggedUser);
		return 0;
	}
	return 1;
}

int LoginManager::login(std::string username, std::string password)
{
	bool logged = m_database->doesPasswordMatch(username, password);
	if (logged)
	{
		LoggedUser loggedUser(username);
		m_loggedUsers.push_back(loggedUser);
		return 0;
	}
	return 1;
}

int LoginManager::logout(std::string username)
{
	for (auto it = m_loggedUsers.begin(); it != m_loggedUsers.end(); it++)
	{
		if (it->getUsername() == username)
		{
			m_loggedUsers.erase(it);
			return 0;
		}
	}
	return 1;
}
