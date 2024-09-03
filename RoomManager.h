#pragma once
#include <iostream>
#include <map>
#include "LoggedUser.h"
#include "Room.h"
class RoomManager
{
public:
	RoomManager();
	int createRoom(LoggedUser logged, RoomData room);
	int deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	std::vector<RoomData> getRooms();
	Room& getRoom(int ID);
private:
	std::map<unsigned int, Room> m_rooms;
};