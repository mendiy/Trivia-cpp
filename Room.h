#pragma once
#include <iostream>
#include <vector>
#include "LoggedUser.h"


struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
}; RoomData;


class Room
{
public:
	Room(RoomData metadata, LoggedUser logged);
	Room(){}
	int addUser(LoggedUser logged);
	int removeUser(LoggedUser logged);
	std::vector<std::string> getAllUsers();
	RoomData getRoom() { return m_metadata; }
	void setIsActive(bool newState);
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;

};