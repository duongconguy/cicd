#include "Hash.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <functional>

// Placeholder: dùng std::hash thay cho SHA-256 thực sự để demo
std::string sha256(const std::string& str) {
    std::hash<std::string> hasher;
    size_t hash = hasher(str);
    std::ostringstream oss;
    oss << std::hex << std::setw(16) << std::setfill('0') << hash;
    return oss.str();
}
// Để bảo mật thực sự, thay thế bằng thư viện SHA-256 thực tế 