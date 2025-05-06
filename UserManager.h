#pragma once
#include "UserAccount.h"
#include <vector>
#include <string>
class UserManager {
public:
    std::vector<UserAccount> users;
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename);
    bool backup(const std::string& backupFile);
    UserAccount* findUser(const std::string& username);
    bool registerUser(const UserAccount& user);
    bool login(const std::string& username, const std::string& password, UserAccount*& outUser);
    bool changePassword(UserAccount& user, const std::string& newPassword);
}; 