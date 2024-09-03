#pragma once

class LoggedUser
{
public: 
	LoggedUser(std::string username) :m_username(username){}
	~LoggedUser(){}
	std::string getUsername() { return m_username; };
private:
	std::string  m_username;
};