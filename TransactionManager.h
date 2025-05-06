#pragma once
#include "Transaction.h"
#include <vector>
#include <string>
class TransactionManager {
public:
    std::vector<Transaction> transactions;
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename);
    bool backup(const std::string& backupFile);
    void logTransaction(const Transaction& tx);
}; 