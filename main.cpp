#include <iostream>
#include <windows.h>
#include "UserManager.h"
#include "WalletManager.h"
#include "TransactionManager.h"
#include "OTPManager.h"
#include "utils.h"
#include "Hash.h"

// Cấu hình console để hiển thị tiếng Việt
void setupConsole() {
    // Đặt code page UTF-8
    SetConsoleOutputCP(65001);
    // Bật chế độ Unicode
    SetConsoleCP(65001);
}

const std::string USER_FILE = "data/users.dat";
const std::string WALLET_FILE = "data/wallets.dat";
const std::string TX_FILE = "data/transactions.dat";
const std::string USER_BK = "data/backup/users_backup.dat";
const std::string WALLET_BK = "data/backup/wallets_backup.dat";
const std::string TX_BK = "data/backup/transactions_backup.dat";

void ensureDataDirs() {
    CreateDirectoryA("data", NULL);
    CreateDirectoryA("data/backup", NULL);
}

void showMenu() {
    std::cout << "\n===== HỆ THỐNG QUẢN LÝ ĐĂNG NHẬP & VÍ ĐIỂM =====\n";
    std::cout << "1. Đăng ký tài khoản\n";
    std::cout << "2. Đăng nhập\n";
    std::cout << "3. Backup dữ liệu\n";
    std::cout << "4. Phục hồi dữ liệu\n";
    std::cout << "0. Thoát\n";
    std::cout << "Chọn: ";
}

int main() {
    setupConsole();
    ensureDataDirs();
    UserManager userMgr;
    WalletManager walletMgr;
    TransactionManager txMgr;
    userMgr.loadFromFile(USER_FILE);
    walletMgr.loadFromFile(WALLET_FILE);
    txMgr.loadFromFile(TX_FILE);
    OTPManager otpMgr;
    int choice;
    while (true) {
        showMenu();
        std::cin >> choice;
        std::cin.ignore();
        if (choice == 1) {
            // Đăng ký tài khoản
            std::string username, password, fullName, email, phone;
            std::cout << "Tên đăng nhập: "; std::getline(std::cin, username);
            std::cout << "Họ tên: "; std::getline(std::cin, fullName);
            std::cout << "Email: "; std::getline(std::cin, email);
            std::cout << "Số điện thoại: "; std::getline(std::cin, phone);
            std::cout << "Mật khẩu (bỏ trống để tự sinh): "; std::getline(std::cin, password);
            bool autoPw = false;
            if (password.empty()) {
                password = generateRandomPassword();
                autoPw = true;
                std::cout << "Mật khẩu tự sinh: " << password << "\n";
            }
            std::string walletId = "WALLET_" + username;
            UserAccount acc(username, sha256(password), fullName, email, phone, UserRole::USER, autoPw, std::time(nullptr), 0, walletId);
            if (userMgr.registerUser(acc)) {
                walletMgr.wallets.push_back(Wallet(walletId, username, 0));
                userMgr.saveToFile(USER_FILE);
                walletMgr.saveToFile(WALLET_FILE);
                std::cout << "Đăng ký thành công!\n";
            } else {
                std::cout << "Tên đăng nhập đã tồn tại!\n";
            }
        } else if (choice == 2) {
            // Đăng nhập
            std::string username, password;
            std::cout << "Tên đăng nhập: "; std::getline(std::cin, username);
            std::cout << "Mật khẩu: "; std::getline(std::cin, password);
            UserAccount* user = nullptr;
            if (userMgr.login(username, password, user)) {
                std::cout << "Đăng nhập thành công!\n";
                // Menu người dùng
                while (true) {
                    std::cout << "\n--- Xin chào, " << user->fullName << " ---\n";
                    std::cout << "1. Xem số dư ví\n";
                    std::cout << "2. Chuyển điểm\n";
                    std::cout << "3. Xem lịch sử giao dịch\n";
                    std::cout << "4. Đổi mật khẩu\n";
                    std::cout << "0. Đăng xuất\n";
                    std::cout << "Chọn: ";
                    int sub;
                    std::cin >> sub; std::cin.ignore();
                    if (sub == 1) {
                        Wallet* w = walletMgr.findWalletByUser(user->username);
                        if (w) std::cout << "Số dư: " << w->balance << " điểm\n";
                        else std::cout << "Không tìm thấy ví!\n";
                    } else if (sub == 2) {
                        std::string toUser; int amount;
                        std::cout << "Chuyển tới (username): "; std::getline(std::cin, toUser);
                        std::cout << "Số điểm: "; std::cin >> amount; std::cin.ignore();
                        Wallet* fromW = walletMgr.findWalletByUser(user->username);
                        Wallet* toW = walletMgr.findWalletByUser(toUser);
                        if (!fromW || !toW) { std::cout << "Ví không tồn tại!\n"; continue; }
                        if (fromW->balance < amount) { std::cout << "Không đủ số dư!\n"; continue; }
                        // OTP xác thực
                        otpMgr.generateOTP(user->username);
                        std::cout << "Mã OTP gửi tới bạn (demo): " << otpMgr.currentOTP << "\n";
                        std::string otp;
                        std::cout << "Nhập OTP: "; std::getline(std::cin, otp);
                        if (!otpMgr.verifyOTP(user->username, otp)) {
                            std::cout << "OTP không hợp lệ!\n"; continue;
                        }
                        fromW->balance -= amount;
                        toW->balance += amount;
                        Transaction tx("TX" + std::to_string(txMgr.transactions.size()+1), fromW->walletId, toW->walletId, amount, std::time(nullptr), "success");
                        txMgr.logTransaction(tx);
                        walletMgr.saveToFile(WALLET_FILE);
                        txMgr.saveToFile(TX_FILE);
                        std::cout << "Chuyển điểm thành công!\n";
                    } else if (sub == 3) {
                        std::cout << "Lịch sử giao dịch:\n";
                        for (const auto& tx : txMgr.transactions) {
                            if (tx.fromWalletId == user->walletId || tx.toWalletId == user->walletId) {
                                std::cout << "ID: " << tx.transactionId << ", Từ: " << tx.fromWalletId << ", Đến: " << tx.toWalletId << ", Số điểm: " << tx.amount << ", Thời gian: " << getCurrentTimeString() << ", Trạng thái: " << tx.status << "\n";
                            }
                        }
                    } else if (sub == 4) {
                        std::string oldPw, newPw;
                        std::cout << "Mật khẩu cũ: "; std::getline(std::cin, oldPw);
                        if (!userMgr.login(user->username, oldPw, user)) {
                            std::cout << "Sai mật khẩu!\n"; continue;
                        }
                        std::cout << "Mật khẩu mới: "; std::getline(std::cin, newPw);
                        userMgr.changePassword(*user, newPw);
                        userMgr.saveToFile(USER_FILE);
                        std::cout << "Đổi mật khẩu thành công!\n";
                    } else if (sub == 0) {
                        break;
                    }
                }
            } else {
                std::cout << "Đăng nhập thất bại!\n";
            }
        } else if (choice == 3) {
            // Backup
            userMgr.backup(USER_BK);
            walletMgr.backup(WALLET_BK);
            txMgr.backup(TX_BK);
            std::cout << "Đã backup dữ liệu!\n";
        } else if (choice == 4) {
            // Phục hồi
            userMgr.loadFromFile(USER_BK);
            walletMgr.loadFromFile(WALLET_BK);
            txMgr.loadFromFile(TX_BK);
            userMgr.saveToFile(USER_FILE);
            walletMgr.saveToFile(WALLET_FILE);
            txMgr.saveToFile(TX_FILE);
            std::cout << "Đã phục hồi dữ liệu từ backup!\n";
        } else if (choice == 0) {
            break;
        }
    }
    return 0;
} 