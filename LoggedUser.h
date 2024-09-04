#pragma once
#include <string>

class LoggedUser
{
public: 
	LoggedUser(std::string username) :m_username(username){}
	~LoggedUser(){}
	std::string getUsername() { return m_username; };
	bool operator==(const LoggedUser& other) const {
		return m_username == other.m_username;
	}
private:
	std::string  m_username;
};