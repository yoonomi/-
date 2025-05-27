#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <ctime>
#include <chrono>
#include <iostream>
#include <limits>

namespace Utils {
    // 时间相关函数
    std::string getCurrentTimeString();  // 获取当前时间 (YYYY-MM-DD HH:MM:SS)
    std::string getCurrentDateString();  // 获取当前日期 (YYYY-MM-DD)
    bool isValidDateFormat(const std::string& date);  // 验证日期格式
    int compareDates(const std::string& date1, const std::string& date2);  // 比较日期
    bool isDateInRange(const std::string& date, const std::string& startDate, const std::string& endDate);  // 检查日期范围
    std::string extractDateFromTimeString(const std::string& timeStr);  // 从时间字符串提取日期

    // 输入验证函数
    bool isValidPhoneNumber(const std::string& phone);  // 验证手机号
    bool isValidTrackingNumber(const std::string& tracking);  // 验证运单号
    std::string generateRandomString(int length);  // 生成随机字符串

    // 控制台输入函数
    template<typename T>
    T getInput(const std::string& prompt, const std::string& errorMsg = "输入无效，请重试：") {
        T value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << errorMsg << std::endl;
        }
    }

    // 获取一行输入
    std::string getLineInput(const std::string& prompt);

    // 清屏函数
    void clearScreen();

    // 等待用户按键继续
    void waitForEnter(const std::string& message = "按回车键继续...");
}

#endif // UTILS_H 