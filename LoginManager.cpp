#include "LoginManager.h"
#include <algorithm>

int LoginManager::Signup(std::string username, std::string password, std::string email)
{
    std::lock_guard<std::mutex> lock(m_loginMutex);
    bool logged = m_database->AddNewUser(username, password, email);
    if (logged)
    {
        LoggedUser loggedUser(username);
        m_loggedUsers.push_back(loggedUser);
        return 0;
    }
    return 1;
}

int LoginManager::Login(std::string username, std::string password)
{
    std::lock_guard<std::mutex> lock(m_loginMutex);

    bool logged = m_database->DoesPasswordMatch(username, password);
    if (logged)
    {
        LoggedUser loggedUser(username);
        m_loggedUsers.push_back(loggedUser);
        return 0;
    }
    return 1;
}

int LoginManager::Logout(std::string username)
{
    std::lock_guard<std::mutex> lock(m_loginMutex);

    for (auto it = m_loggedUsers.begin(); it != m_loggedUsers.end(); it++)
    {
        if (it->GetUsername() == username)
        {
            m_loggedUsers.erase(it);
            return 0;
        }
    }
    return 1;
}
