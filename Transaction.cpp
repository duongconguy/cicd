#include "Transaction.h"
#include <sstream>
#include <vector>

Transaction::Transaction() : amount(0), timestamp(0), status("pending") {}
Transaction::Transaction(const std::string& transactionId, const std::string& fromWalletId, const std::string& toWalletId, int amount, time_t timestamp, const std::string& status)
    : transactionId(transactionId), fromWalletId(fromWalletId), toWalletId(toWalletId), amount(amount), timestamp(timestamp), status(status) {}

std::string Transaction::serialize() const {
    std::ostringstream oss;
    oss << transactionId << ',' << fromWalletId << ',' << toWalletId << ',' << amount << ',' << timestamp << ',' << status;
    return oss.str();
}

Transaction Transaction::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(iss, token, ',')) tokens.push_back(token);
    if (tokens.size() < 6) return Transaction();
    return Transaction(tokens[0], tokens[1], tokens[2], std::stoi(tokens[3]), std::stol(tokens[4]), tokens[5]);
} 