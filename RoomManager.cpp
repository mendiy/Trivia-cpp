#include "RoomManager.h"

RoomManager::RoomManager()
{

}

int RoomManager::createRoom(LoggedUser logged, RoomData room)
{
	std::lock_guard<std::mutex> lock(m_roomMutex);

	Room newRoom(room, logged);
	m_rooms[room.id] = newRoom;
	return 0;
}

int RoomManager::deleteRoom(int ID)
{
	std::lock_guard<std::mutex> lock(m_roomMutex);
	m_rooms.erase(ID);
	return 0;
}

unsigned int RoomManager::getRoomState(int ID)
{
	std::lock_guard<std::mutex> lock(m_roomMutex);

	return m_rooms[ID].getRoom().isActive;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::lock_guard<std::mutex> lock(m_roomMutex);
	std::vector<RoomData> allRooms;
	for (auto it = m_rooms.begin(); it != m_rooms.end(); it++)
	{
		allRooms.push_back(it->second.getRoom());
	}
	return allRooms;
}

Room& RoomManager::getRoom(int ID)
{
	std::lock_guard<std::mutex> lock(m_roomMutex);
	return m_rooms[ID];
}
