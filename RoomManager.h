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
    int CreateRoom(LoggedUser logged, RoomData room);
    int DeleteRoom(int ID);
    unsigned int GetRoomState(int ID);
    void SetIsActive(int ID, bool newState);
    std::vector<RoomData> GetRooms();
    Room& GetRoomMeatdata(int ID);
private:
    static int m_id;
    std::map<unsigned int, Room> m_rooms;
    std::mutex m_roomMutex;

};