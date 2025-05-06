#pragma once
#include <string>
#include <ctime>
class Transaction {
public:
    std::string transactionId;
    std::string fromWalletId;
    std::string toWalletId;
    int amount;
    time_t timestamp;
    std::string status; // success, failed, pending
    Transaction();
    Transaction(const std::string& transactionId, const std::string& fromWalletId, const std::string& toWalletId, int amount, time_t timestamp, const std::string& status);
    std::string serialize() const;
    static Transaction deserialize(const std::string& data);
}; 