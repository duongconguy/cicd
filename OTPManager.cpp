#include "OTPManager.h"
#include <random>
#include <ctime>

OTPManager::OTPManager() : generatedAt(0), isUsed(true) {}

void OTPManager::generateOTP(const std::string& username) {
    this->username = username;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000, 999999);
    currentOTP = std::to_string(dis(gen));
    generatedAt = std::time(nullptr);
    isUsed = false;
}

bool OTPManager::verifyOTP(const std::string& username, const std::string& otp) {
    time_t now = std::time(nullptr);
    if (isUsed) return false;
    if (this->username != username) return false;
    if (currentOTP != otp) return false;
    if (now - generatedAt > 300) return false; // 5 phút
    isUsed = true;
    return true;
} 