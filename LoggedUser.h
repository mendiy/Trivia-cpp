#pragma once
#include <string>

class LoggedUser
{
public: 
	LoggedUser(std::string username) :m_username(username){}
	~LoggedUser(){}
	LoggedUser(const LoggedUser& other) = default;
	LoggedUser& operator=(const LoggedUser& other) = default;
	bool operator==(const LoggedUser& other) const {
		return m_username == other.m_username;
	}
	bool operator<(const LoggedUser& other) const {
		return this->m_username < other.m_username;
	}
	std::string getUsername() { return m_username; };
private:
	std::string  m_username;

};