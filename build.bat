@echo off
echo 正在编译项目...
C:\MinGW\bin\g++.exe -std=c++14 -Wall -Wextra main.cpp Package.cpp DatabaseManager.cpp SystemManager.cpp utils.cpp -o express_system
if %errorlevel% equ 0 (
    echo 编译成功！
    echo 正在启动程序...
    express_system.exe
) else (
    echo 编译失败！
    pause
) 