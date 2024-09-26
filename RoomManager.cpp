#include "RoomManager.h"
#include <algorithm>

int RoomManager::m_id;
RoomManager::RoomManager()
{
    m_id = 1;
}

int RoomManager::CreateRoom(LoggedUser logged, RoomData room)
{
    std::lock_guard<std::mutex> lock(m_roomMutex);
    room.id = m_id;
    room.isActive = false;
    m_id++;
    for (auto it = m_rooms.begin(); it != m_rooms.end(); it++)
    {
        if ((it->second.GetRoom().name) == room.name)
        {
            return 0;
        }
    }

    Room newRoom(room, logged);
    m_rooms[room.id] = newRoom;
    return room.id;
}

int RoomManager::DeleteRoom(int ID)
{
    std::lock_guard<std::mutex> lock(m_roomMutex);
    m_rooms.erase(ID);
    return 0;
}

unsigned int RoomManager::GetRoomState(int ID)
{
    std::lock_guard<std::mutex> lock(m_roomMutex);

    return m_rooms[ID].GetRoom().isActive;
}

void RoomManager::SetIsActive(int ID, bool newState)
{
    std::lock_guard<std::mutex> lock(m_roomMutex);

    m_rooms[ID].SetIsActive(newState);
}

std::vector<RoomData> RoomManager::GetRooms()
{
    std::lock_guard<std::mutex> lock(m_roomMutex);
    std::vector<RoomData> allRooms;
    for (auto it = m_rooms.begin(); it != m_rooms.end(); it++)
    {
        allRooms.push_back(it->second.GetRoom());
    }
    return allRooms;
}

Room& RoomManager::GetRoomMeatdata(int ID)
{
    std::lock_guard<std::mutex> lock(m_roomMutex);
    return m_rooms[ID];
}
