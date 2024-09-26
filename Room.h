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
    int AddUser(LoggedUser logged);
    int RemoveUser(LoggedUser logged);
    std::vector<std::string> GetAllUsers();
    RoomData GetRoom() { return m_metadata; }
    void SetIsActive(bool newState);
private:
    RoomData m_metadata;
    std::vector<LoggedUser> m_users;

};