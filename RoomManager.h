#pragma once
#include <iostream>
#include <map>
#include "LoggedUser.h"
#include "Room.h"
#include <mutex>
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
	static int m_id;
	std::map<unsigned int, Room> m_rooms;
	std::mutex m_roomMutex;

};