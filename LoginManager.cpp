#include "LoginManager.h"
#include <algorithm>

int LoginManager::signup(std::string username, std::string password, std::string email)
{
    std::lock_guard<std::mutex> lock(m_loginMutex);
    bool logged = m_database->addNewUser(username, password, email);
    if (logged)
    {
        LoggedUser loggedUser(username);
        m_loggedUsers.push_back(loggedUser);
        return 0;
    }
    return 1;
}

int LoginManager::login(std::string username, std::string password)
{
    std::lock_guard<std::mutex> lock(m_loginMutex);

    bool logged = m_database->doesPasswordMatch(username, password);
    if (logged)
    {
        LoggedUser loggedUser(username);
        m_loggedUsers.push_back(loggedUser);
        return 0;
    }
    return 1;
}

int LoginManager::logout(std::string username)
{
    std::lock_guard<std::mutex> lock(m_loginMutex);

    for (auto it = m_loggedUsers.begin(); it != m_loggedUsers.end(); it++)
    {
        if (it->getUsername() == username)
        {
            m_loggedUsers.erase(it);
            return 0;
        }
    }
    return 1;
}
