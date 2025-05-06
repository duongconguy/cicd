#pragma once
#include "Wallet.h"
#include <vector>
#include <string>
class WalletManager {
public:
    std::vector<Wallet> wallets;
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename);
    bool backup(const std::string& backupFile);
    Wallet* findWallet(const std::string& walletId);
    Wallet* findWalletByUser(const std::string& username);
}; 