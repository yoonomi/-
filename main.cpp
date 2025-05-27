#include <iostream>
#include <stdexcept>
#include "SystemManager.h"
#include "utils.h"
#include <windows.h>

int main() {
    try {
        // 设置控制台编码（Windows系统）
#ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
#endif

        SetConsoleOutputCP(65001);  // 使用 UTF-8 编码

        // 创建系统管理器实例
        SystemManager system("packages.csv");

        // 显示欢迎信息
        Utils::clearScreen();
        std::cout << "=================================" << std::endl;
        std::cout << "    欢迎使用快件管理系统" << std::endl;
        std::cout << "=================================" << std::endl;
        Utils::waitForEnter();

        // 运行系统
        system.run();

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "\n错误: " << e.what() << std::endl;
        Utils::waitForEnter("按回车键退出...");
        return 1;
    }
    catch (...) {
        std::cerr << "\n发生未知错误！" << std::endl;
        Utils::waitForEnter("按回车键退出...");
        return 1;
    }
} 