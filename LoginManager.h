#pragma once
#include <iostream>
#include <vector>
#include "IDatabase.h"
#include "LoggedUser.h"
#include "SqliteDataBase.h"
#include <mutex>


class LoginManager
{
    public:
        LoginManager(IDatabase* database) : m_database(database) {};
        ~LoginManager() {};
        int signup(std::string username, std::string password, std::string email);
        int login(std::string username, std::string password);
        int logout(std::string username);
    private:
        IDatabase* m_database;
        std::vector<LoggedUser> m_loggedUsers;
        std::mutex m_loginMutex;
};
