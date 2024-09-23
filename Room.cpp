#include "Room.h"

Room::Room(RoomData metadata, LoggedUser logged)
{
    m_metadata = metadata;
    m_users.push_back(logged);
}

int Room::addUser(LoggedUser logged)
{
	if (m_metadata.maxPlayers == m_users.size())
	{
		std::cout << "Room Size" << m_users.size() << "\n";
		return 1;
	}
    m_users.push_back(logged);
    return 0;
}

int Room::removeUser(LoggedUser logged)
{
	for (auto it = m_users.begin(); it != m_users.end(); it++)
	{
		if (logged.getUsername() == it->getUsername())
		{
			m_users.erase(it);
			return 0;
		}
	}
   
    return 1;
}

std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> allUsers;
	for (auto it = m_users.begin(); it != m_users.end(); it++)
	{
		
		allUsers.push_back(it->getUsername());
		
	}
    return allUsers;
}

void Room::setIsActive(bool newState)
{
	m_metadata.isActive = newState;
}
