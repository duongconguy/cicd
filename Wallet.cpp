#include "Wallet.h"
#include <sstream>
#include <vector>

Wallet::Wallet() : balance(0) {}
Wallet::Wallet(const std::string& walletId, const std::string& ownerUsername, int balance)
    : walletId(walletId), ownerUsername(ownerUsername), balance(balance) {}

std::string Wallet::serialize() const {
    std::ostringstream oss;
    oss << walletId << ',' << ownerUsername << ',' << balance;
    return oss.str();
}

Wallet Wallet::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(iss, token, ',')) tokens.push_back(token);
    if (tokens.size() < 3) return Wallet();
    return Wallet(tokens[0], tokens[1], std::stoi(tokens[2]));
} 