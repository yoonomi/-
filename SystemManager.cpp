#include "SystemManager.h"
#include <iostream>
#include <limits>
#include <map>
#include <algorithm>
#include "utils.h"

// 构造函数
SystemManager::SystemManager(const std::string& dbPath) 
    : dbManager(dbPath), isLoggedIn(false) {
    personnelPassword = "123456";  // 设置默认密码
    loadData();
}

// 系统运行主循环
void SystemManager::run() {
    while (true) {
        displayMainMenu();
        int choice;
        std::cout << "请选择操作 (1-3): ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:  // 服务人员登录
                if (loginPersonnel()) {
                    displayPersonnelMenu();
                }
                break;
            case 2:  // 收件人菜单
                displayRecipientMenu();
                break;
            case 3:  // 退出系统
                saveData();
                std::cout << "感谢使用，再见！" << std::endl;
                return;
            default:
                std::cout << "无效的选择，请重试。" << std::endl;
        }
    }
}

// 显示主菜单
void SystemManager::displayMainMenu() {
    std::cout << "\n=== 快件管理系统 ===" << std::endl;
    std::cout << "1. 服务人员登录" << std::endl;
    std::cout << "2. 收件人服务" << std::endl;
    std::cout << "3. 退出系统" << std::endl;
}

// 显示服务人员菜单
void SystemManager::displayPersonnelMenu() {
    while (isLoggedIn) {
        std::cout << "\n=== 服务人员菜单 ===" << std::endl;
        std::cout << "1. 录入快件" << std::endl;
        std::cout << "2. 修改快件" << std::endl;
        std::cout << "3. 删除快件" << std::endl;
        std::cout << "4. 查询快件" << std::endl;
        std::cout << "5. 统计信息" << std::endl;
        std::cout << "6. 退出登录" << std::endl;

        int choice;
        std::cout << "请选择操作 (1-6): ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                addPackage();
                break;
            case 2:
                modifyPackage();
                break;
            case 3:
                deletePackage();
                break;
            case 4:
                queryPackagePersonnel();
                break;
            case 5:
                showStatistics();
                break;
            case 6:
                isLoggedIn = false;
                std::cout << "已退出登录" << std::endl;
                return;
            default:
                std::cout << "无效的选择，请重试。" << std::endl;
        }
    }
}

// 显示收件人菜单
void SystemManager::displayRecipientMenu() {
    while (true) {
        std::cout << "\n=== 收件人服务 ===" << std::endl;
        std::cout << "1. 查询快件" << std::endl;
        std::cout << "2. 取件" << std::endl;
        std::cout << "3. 返回主菜单" << std::endl;

        int choice;
        std::cout << "请选择操作 (1-3): ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                queryPackageRecipient();
                break;
            case 2:
                pickupPackage();
                break;
            case 3:
                return;
            default:
                std::cout << "无效的选择，请重试。" << std::endl;
        }
    }
}

// 服务人员登录
bool SystemManager::loginPersonnel() {
    const int MAX_ATTEMPTS = 3;
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS) {
        std::string password;
        std::cout << "请输入服务人员密码: ";
        std::getline(std::cin, password);

        if (password == personnelPassword) {
            isLoggedIn = true;
            std::cout << "登录成功！" << std::endl;
            return true;
        } else {
            attempts++;
            std::cout << "密码错误！还剩 " << (MAX_ATTEMPTS - attempts) << " 次尝试机会。" << std::endl;
        }
    }

    std::cout << "登录失败次数过多，请稍后再试。" << std::endl;
    return false;
}

// 加载数据
void SystemManager::loadData() {
    if (!dbManager.loadPackages(packages)) {
        std::cout << "警告：加载数据失败！" << std::endl;
    }
}

// 保存数据
void SystemManager::saveData() {
    if (!dbManager.savePackages(packages)) {
        std::cerr << "保存数据失败！" << std::endl;
    }
}

// 收件人查询快件
void SystemManager::queryPackageRecipient() {
    std::string phone;
    std::cout << "\n=== 快件查询 ===" << std::endl;
    std::cout << "请输入您的手机号: ";
    std::getline(std::cin, phone);

    if (!Utils::isValidPhoneNumber(phone)) {
        std::cout << "无效的手机号格式！" << std::endl;
        return;
    }

    bool found = false;
    std::cout << "\n您的待取快件：" << std::endl;
    std::cout << "------------------------" << std::endl;

    for (const auto& package : packages) {
        if (package.getRecipientPhone() == phone && !package.getIsPickedUp()) {
            package.displayDetails();
            std::cout << "------------------------" << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "没有找到您的待取快件。" << std::endl;
    }
}

// 取件功能
void SystemManager::pickupPackage() {
    std::cout << "\n=== 取件服务 ===" << std::endl;
    std::cout << "请选择取件凭据类型：" << std::endl;
    std::cout << "1. 取件码" << std::endl;
    std::cout << "2. 手机号" << std::endl;
    std::cout << "3. 运单号" << std::endl;
    std::cout << "0. 返回" << std::endl;

    int choice;
    std::cout << "请选择 (0-3): ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 0) {
        return;
    }

    if (choice < 1 || choice > 3) {
        std::cout << "无效的选择！" << std::endl;
        return;
    }

    std::string credential;
    std::cout << "请输入" << (choice == 1 ? "取件码" : choice == 2 ? "手机号" : "运单号") << ": ";
    std::getline(std::cin, credential);

    // 验证输入格式
    if (choice == 2 && !Utils::isValidPhoneNumber(credential)) {
        std::cout << "无效的手机号格式！" << std::endl;
        return;
    } else if (choice == 3 && !Utils::isValidTrackingNumber(credential)) {
        std::cout << "无效的运单号格式！" << std::endl;
        return;
    }

    // 查找快件
    Package* package = findPackage(credential, choice);
    if (!package) {
        std::cout << "未找到相关快件！" << std::endl;
        return;
    }

    // 检查是否已取件
    if (package->getIsPickedUp()) {
        std::cout << "该快件已被取走！" << std::endl;
        return;
    }

    // 显示快件信息并确认
    std::cout << "\n找到以下快件：" << std::endl;
    package->displayDetails();
    
    std::cout << "\n确认取件？(y/n): ";
    char confirm;
    std::cin >> confirm;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (confirm == 'y' || confirm == 'Y') {
        package->markAsPickedUp();
        std::cout << "\n取件成功！" << std::endl;
        std::cout << "感谢使用我们的服务！" << std::endl;
    } else {
        std::cout << "已取消取件" << std::endl;
    }
}

// 显示统计菜单
void SystemManager::showStatistics() {
    if (!isLoggedIn) {
        std::cout << "请先登录！" << std::endl;
        return;
    }

    while (true) {
        std::cout << "\n=== 统计信息 ===" << std::endl;
        std::cout << "1. 按时间段统计" << std::endl;
        std::cout << "2. 按快递公司统计" << std::endl;
        std::cout << "0. 返回" << std::endl;

        int choice;
        std::cout << "请选择统计方式 (0-2): ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                statsByTime();
                break;
            case 2:
                statsByCompany();
                break;
            case 0:
                return;
            default:
                std::cout << "无效的选择！" << std::endl;
        }
    }
}

// 按时间段统计
void SystemManager::statsByTime() {
    std::string startDate, endDate;
    
    std::cout << "\n请输入开始日期 (YYYY-MM-DD): ";
    std::getline(std::cin, startDate);
    if (!Utils::isValidDateFormat(startDate)) {
        std::cout << "无效的开始日期格式！" << std::endl;
        return;
    }

    std::cout << "请输入结束日期 (YYYY-MM-DD): ";
    std::getline(std::cin, endDate);
    if (!Utils::isValidDateFormat(endDate)) {
        std::cout << "无效的结束日期格式！" << std::endl;
        return;
    }

    if (startDate > endDate) {
        std::cout << "开始日期不能晚于结束日期！" << std::endl;
        return;
    }

    int totalReceived = 0;    // 总收件量
    int totalPickedUp = 0;    // 总取件量
    int totalUnpicked = 0;    // 总未取件量

    for (const auto& package : packages) {
        std::string arrivalDate = Utils::extractDateFromTimeString(package.getArrivalTime());
        std::string pickupDate = package.getIsPickedUp() ? 
            Utils::extractDateFromTimeString(package.getPickupTime()) : "";

        // 检查是否在时间范围内
        if (Utils::isDateInRange(arrivalDate, startDate, endDate)) {
            totalReceived++;
            
            if (package.getIsPickedUp()) {
                if (Utils::isDateInRange(pickupDate, startDate, endDate)) {
                    totalPickedUp++;
                }
            } else {
                totalUnpicked++;
            }
        }
    }

    // 显示统计结果
    std::cout << "\n=== 统计结果 (" << startDate << " 至 " << endDate << ") ===" << std::endl;
    std::cout << "总收件量: " << totalReceived << std::endl;
    std::cout << "总取件量: " << totalPickedUp << std::endl;
    std::cout << "未取件量: " << totalUnpicked << std::endl;
    std::cout << "取件率: " << (totalReceived > 0 ? 
        (static_cast<double>(totalPickedUp) / totalReceived * 100) : 0) 
        << "%" << std::endl;
}

// 按快递公司统计
void SystemManager::statsByCompany() {
    std::string currentDate = Utils::getCurrentDateString();
    std::map<std::string, int> companyStats;

    // 统计每个快递公司的收件量
    for (const auto& package : packages) {
        std::string arrivalDate = Utils::extractDateFromTimeString(package.getArrivalTime());
        if (arrivalDate == currentDate) {
            companyStats[package.getCourierCompany()]++;
        }
    }

    // 显示统计结果
    std::cout << "\n=== 今日快递公司收件统计 (" << currentDate << ") ===" << std::endl;
    if (companyStats.empty()) {
        std::cout << "今日暂无收件记录" << std::endl;
        return;
    }

    int total = 0;
    for (const auto& stat : companyStats) {
        std::cout << stat.first << ": " << stat.second << "件" << std::endl;
        total += stat.second;
    }
    std::cout << "------------------------" << std::endl;
    std::cout << "总计: " << total << "件" << std::endl;
}

// 添加快件
void SystemManager::addPackage() {
    if (!isLoggedIn) {
        std::cout << "请先登录！" << std::endl;
        return;
    }

    std::string tracking, name, phone, company, category;
    double weight;

    std::cout << "\n=== 录入快件 ===" << std::endl;
    
    // 输入运单号
    do {
        std::cout << "请输入运单号: ";
        std::getline(std::cin, tracking);
    } while (!Utils::isValidTrackingNumber(tracking));

    // 检查运单号是否已存在
    if (dbManager.findPackage(tracking)) {
        std::cout << "该运单号已存在！" << std::endl;
        return;
    }

    // 输入收件人信息
    std::cout << "请输入收件人姓名: ";
    std::getline(std::cin, name);

    // 输入手机号
    do {
        std::cout << "请输入收件人手机号: ";
        std::getline(std::cin, phone);
    } while (!Utils::isValidPhoneNumber(phone));

    // 输入快递公司
    std::cout << "请输入快递公司: ";
    std::getline(std::cin, company);

    // 输入重量
    do {
        std::cout << "请输入重量(kg): ";
        std::cin >> weight;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (weight <= 0);

    // 输入类别
    std::cout << "请输入类别(文件/普通/易碎): ";
    std::getline(std::cin, category);

    // 创建新快件
    Package package;
    package.setDetails(tracking, name, phone, company, weight, category);
    package.generatePickupCode(packages.size() + 1);

    // 保存快件
    if (dbManager.savePackage(package)) {
        packages.push_back(package);
        std::cout << "\n快件录入成功！" << std::endl;
        std::cout << "取件码: " << package.getPickupCode() << std::endl;
    } else {
        std::cout << "快件录入失败！" << std::endl;
    }
}

// 修改快件
void SystemManager::modifyPackage() {
    if (!isLoggedIn) {
        std::cout << "请先登录！" << std::endl;
        return;
    }

    std::string tracking;
    std::cout << "\n=== 修改快件 ===" << std::endl;
    std::cout << "请输入要修改的快件运单号: ";
    std::getline(std::cin, tracking);

    Package* package = dbManager.findPackage(tracking);
    if (!package) {
        std::cout << "未找到该快件！" << std::endl;
        return;
    }

    if (package->getIsPickedUp()) {
        std::cout << "该快件已被取走，无法修改！" << std::endl;
        return;
    }

    std::string name, phone, company, category;
    double weight;

    // 显示当前信息
    std::cout << "\n当前快件信息：" << std::endl;
    package->displayDetails();

    // 输入新信息
    std::cout << "\n请输入新信息（直接回车表示不修改）：" << std::endl;
    
    std::cout << "收件人姓名 [" << package->getRecipientName() << "]: ";
    std::getline(std::cin, name);
    if (!name.empty()) {
        package->setDetails(package->getTrackingNumber(), name,
                          package->getRecipientPhone(), package->getCourierCompany(),
                          package->getWeight(), package->getCategory());
    }

    std::cout << "手机号 [" << package->getRecipientPhone() << "]: ";
    std::getline(std::cin, phone);
    if (!phone.empty() && Utils::isValidPhoneNumber(phone)) {
        package->setDetails(package->getTrackingNumber(), package->getRecipientName(),
                          phone, package->getCourierCompany(),
                          package->getWeight(), package->getCategory());
    }

    std::cout << "快递公司 [" << package->getCourierCompany() << "]: ";
    std::getline(std::cin, company);
    if (!company.empty()) {
        package->setDetails(package->getTrackingNumber(), package->getRecipientName(),
                          package->getRecipientPhone(), company,
                          package->getWeight(), package->getCategory());
    }

    std::cout << "重量 [" << package->getWeight() << "]: ";
    std::string weightStr;
    std::getline(std::cin, weightStr);
    if (!weightStr.empty()) {
        try {
            weight = std::stod(weightStr);
            if (weight > 0) {
                package->setDetails(package->getTrackingNumber(), package->getRecipientName(),
                                  package->getRecipientPhone(), package->getCourierCompany(),
                                  weight, package->getCategory());
            }
        } catch (...) {
            std::cout << "无效的重量值！" << std::endl;
        }
    }

    std::cout << "类别 [" << package->getCategory() << "]: ";
    std::getline(std::cin, category);
    if (!category.empty()) {
        package->setDetails(package->getTrackingNumber(), package->getRecipientName(),
                          package->getRecipientPhone(), package->getCourierCompany(),
                          package->getWeight(), category);
    }

    // 更新数据库
    if (dbManager.updatePackage(*package)) {
        std::cout << "\n快件信息修改成功！" << std::endl;
    } else {
        std::cout << "快件信息修改失败！" << std::endl;
    }
}

// 删除快件
void SystemManager::deletePackage() {
    if (!isLoggedIn) {
        std::cout << "请先登录！" << std::endl;
        return;
    }

    std::string tracking;
    std::cout << "\n=== 删除快件 ===" << std::endl;
    std::cout << "请输入要删除的快件运单号: ";
    std::getline(std::cin, tracking);

    Package* package = dbManager.findPackage(tracking);
    if (!package) {
        std::cout << "未找到该快件！" << std::endl;
        return;
    }

    if (package->getIsPickedUp()) {
        std::cout << "该快件已被取走，无法删除！" << std::endl;
        return;
    }

    std::cout << "\n确认删除以下快件？" << std::endl;
    package->displayDetails();
    std::cout << "\n请输入 'y' 确认删除，其他键取消: ";
    char confirm;
    std::cin >> confirm;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (confirm == 'y' || confirm == 'Y') {
        if (dbManager.deletePackage(tracking)) {
            // 从内存中删除
            packages.erase(std::remove_if(packages.begin(), packages.end(),
                [&](const Package& p) { return p.getTrackingNumber() == tracking; }),
                packages.end());
            std::cout << "快件删除成功！" << std::endl;
        } else {
            std::cout << "快件删除失败！" << std::endl;
        }
    } else {
        std::cout << "已取消删除操作" << std::endl;
    }
}

// 服务人员查询快件
void SystemManager::queryPackagePersonnel() {
    if (!isLoggedIn) {
        std::cout << "请先登录！" << std::endl;
        return;
    }

    std::cout << "\n=== 快件查询 ===" << std::endl;
    std::cout << "1. 按运单号查询" << std::endl;
    std::cout << "2. 按手机号查询" << std::endl;
    std::cout << "3. 按取件码查询" << std::endl;
    std::cout << "0. 返回" << std::endl;

    int choice;
    std::cout << "请选择查询方式 (0-3): ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 0) {
        return;
    }

    std::string query;
    std::cout << "请输入查询内容: ";
    std::getline(std::cin, query);

    bool found = false;
    for (const auto& package : packages) {
        bool match = false;
        switch (choice) {
            case 1:
                match = (package.getTrackingNumber() == query);
                break;
            case 2:
                match = (package.getRecipientPhone() == query);
                break;
            case 3:
                match = (package.getPickupCode() == query);
                break;
        }

        if (match) {
            if (!found) {
                std::cout << "\n查询结果：" << std::endl;
                std::cout << "------------------------" << std::endl;
            }
            package.displayDetails();
            std::cout << "------------------------" << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "未找到相关快件！" << std::endl;
    }
}

// 查找快件（根据凭据类型）
Package* SystemManager::findPackage(const std::string& credential, int type) {
    for (auto& package : packages) {
        bool match = false;
        switch (type) {
            case 1:  // 取件码
                match = (package.getPickupCode() == credential);
                break;
            case 2:  // 手机号
                match = (package.getRecipientPhone() == credential);
                break;
            case 3:  // 运单号
                match = (package.getTrackingNumber() == credential);
                break;
        }
        if (match) {
            return &package;
        }
    }
    return nullptr;
} 