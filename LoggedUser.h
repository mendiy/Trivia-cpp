#pragma once

class LoggedUser
{
public: 
	LoggedUser(){}
	~LoggedUser(){}
	std::string getUsername() { return m_username; };
private:
	std::string  m_username;



};