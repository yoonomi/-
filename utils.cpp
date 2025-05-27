#include "utils.h"
#include <sstream>
#include <iomanip>
#include <random>
#include <regex>
#include <chrono>
#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

// 时间相关函数实现
std::string Utils::getCurrentTimeString() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string Utils::getCurrentDateString() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d");
    return ss.str();
}

bool Utils::isValidDateFormat(const std::string& date) {
    std::regex pattern("^\\d{4}-(?:0[1-9]|1[0-2])-(?:0[1-9]|[12]\\d|3[01])$");
    if (!std::regex_match(date, pattern)) {
        return false;
    }

    // 解析日期
    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));

    // 检查月份和日期的有效性
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    // 检查特定月份的天数
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        return day <= (isLeapYear ? 29 : 28);
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return day <= 30;
    }
    return true;
}

int Utils::compareDates(const std::string& date1, const std::string& date2) {
    if (date1 < date2) return -1;
    if (date1 > date2) return 1;
    return 0;
}

bool Utils::isDateInRange(const std::string& date, const std::string& startDate, const std::string& endDate) {
    return date >= startDate && date <= endDate;
}

std::string Utils::extractDateFromTimeString(const std::string& timeStr) {
    return timeStr.substr(0, 10);  // 提取 YYYY-MM-DD 部分
}

// 输入验证函数实现
bool Utils::isValidPhoneNumber(const std::string& phone) {
    std::regex pattern("^1[3-9]\\d{9}$");  // 中国大陆手机号格式
    return std::regex_match(phone, pattern);
}

bool Utils::isValidTrackingNumber(const std::string& tracking) {
    // 运单号格式：字母数字组合，长度8-20位
    std::regex pattern("^[A-Za-z0-9]{8,20}$");
    return std::regex_match(tracking, pattern);
}

std::string Utils::generateRandomString(int length) {
    const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, chars.length() - 1);
    
    std::string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result += chars[dis(gen)];
    }
    return result;
}

// 控制台输入函数实现
std::string Utils::getLineInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

// 清屏函数实现
void Utils::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// 等待用户按键继续
void Utils::waitForEnter(const std::string& message) {
    std::cout << message;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
} 