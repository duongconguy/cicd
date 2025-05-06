#include "WalletManager.h"
#include <fstream>
#include <sstream>

bool WalletManager::loadFromFile(const std::string& filename) {
    wallets.clear();
    std::ifstream fin(filename);
    if (!fin) return false;
    std::string line;
    while (std::getline(fin, line)) {
        if (!line.empty()) wallets.push_back(Wallet::deserialize(line));
    }
    return true;
}

bool WalletManager::saveToFile(const std::string& filename) {
    std::ofstream fout(filename);
    if (!fout) return false;
    for (const auto& wallet : wallets) {
        fout << wallet.serialize() << "\n";
    }
    return true;
}

bool WalletManager::backup(const std::string& backupFile) {
    return saveToFile(backupFile);
}

Wallet* WalletManager::findWallet(const std::string& walletId) {
    for (auto& wallet : wallets) {
        if (wallet.walletId == walletId) return &wallet;
    }
    return nullptr;
}

Wallet* WalletManager::findWalletByUser(const std::string& username) {
    for (auto& wallet : wallets) {
        if (wallet.ownerUsername == username) return &wallet;
    }
    return nullptr; 
} 