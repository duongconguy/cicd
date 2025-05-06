#include "TransactionManager.h"
#include <fstream>
#include <sstream>

bool TransactionManager::loadFromFile(const std::string& filename) {
    transactions.clear();
    std::ifstream fin(filename);
    if (!fin) return false;
    std::string line;
    while (std::getline(fin, line)) {
        if (!line.empty()) transactions.push_back(Transaction::deserialize(line));
    }
    return true;
}

bool TransactionManager::saveToFile(const std::string& filename) {
    std::ofstream fout(filename);
    if (!fout) return false;
    for (const auto& tx : transactions) {
        fout << tx.serialize() << "\n";
    }
    return true;
}

bool TransactionManager::backup(const std::string& backupFile) {
    return saveToFile(backupFile);
}

void TransactionManager::logTransaction(const Transaction& tx) {
    transactions.push_back(tx);
} 