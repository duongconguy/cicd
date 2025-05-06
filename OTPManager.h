#pragma once
#include <string>
#include <ctime>
class OTPManager {
public:
    std::string currentOTP;
    std::string username;
    time_t generatedAt;
    bool isUsed;
    OTPManager();
    void generateOTP(const std::string& username);
    bool verifyOTP(const std::string& username, const std::string& otp);
}; 