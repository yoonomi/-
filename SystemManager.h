#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <vector>
#include <string>
#include <map>
#include "Package.h"
#include "DatabaseManager.h"

class SystemManager {
private:
    std::vector<Package> packages;          // 存储所有快件
    DatabaseManager dbManager;              // 数据管理器
    std::string personnelPassword;          // 服务人员密码
    bool isLoggedIn;                        // 当前是否登录

    // 菜单显示函数
    void displayMainMenu();
    void displayPersonnelMenu();
    void displayRecipientMenu();

    // 登录相关
    bool loginPersonnel();

    // 快件管理功能
    void addPackage();                      // 录入快件
    void modifyPackage();                   // 修改快件
    void deletePackage();                   // 删除快件
    void queryPackagePersonnel();           // 服务人员查询
    void queryPackageRecipient();           // 收件人查询
    void pickupPackage();                   // 取件

    // 统计功能
    void showStatistics();                  // 显示统计
    void statsByTime();                     // 按时间段统计
    void statsByCompany();                  // 按快递公司统计

    // 辅助功能
    int getDailyCount(const std::string& date_str);  // 获取某日快件计数
    Package* findPackage(const std::string& key, int mode);  // 查找快件
    void loadData();                        // 加载数据
    void saveData();                        // 保存数据

public:
    // 构造函数
    SystemManager(const std::string& dbPath);
    
    // 系统运行
    void run();                            // 启动并运行系统主循环
};

#endif // SYSTEM_MANAGER_H 