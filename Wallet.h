#pragma once
#include <string>
class Wallet {
public:
    std::string walletId;
    std::string ownerUsername;
    int balance;
    Wallet();
    Wallet(const std::string& walletId, const std::string& ownerUsername, int balance);
    std::string serialize() const;
    static Wallet deserialize(const std::string& data);
}; 