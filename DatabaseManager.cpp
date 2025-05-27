#include "DatabaseManager.h"
#include <fstream>
#include <iostream>
#include <algorithm>

DatabaseManager::DatabaseManager(const std::string& path) : databasePath(path) {}

bool DatabaseManager::savePackage(const Package& package) {
    std::ofstream file(databasePath, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "无法打开数据库文件进行写入！" << std::endl;
        return false;
    }

    file << package.toCsvString() << std::endl;
    return true;
}

bool DatabaseManager::loadPackages(std::vector<Package>& packages) {
    std::ifstream file(databasePath);
    if (!file.is_open()) {
        // 如果文件不存在，创建一个空文件
        std::ofstream createFile(databasePath);
        if (!createFile.is_open()) {
            std::cerr << "无法创建数据库文件！" << std::endl;
            return false;
        }
        return true;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            Package package;
            package.fromCsvString(line);
            packages.push_back(package);
        }
    }
    return true;
}

bool DatabaseManager::updatePackage(const Package& package) {
    std::vector<Package> packages;
    if (!loadPackages(packages)) {
        return false;
    }

    bool found = false;
    for (auto& p : packages) {
        if (p.getTrackingNumber() == package.getTrackingNumber()) {
            p = package;
            found = true;
            break;
        }
    }

    if (!found) {
        return false;
    }

    // 重写整个文件
    std::ofstream file(databasePath, std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "无法打开数据库文件进行更新！" << std::endl;
        return false;
    }

    for (const auto& p : packages) {
        file << p.toCsvString() << std::endl;
    }
    return true;
}

bool DatabaseManager::deletePackage(const std::string& trackingNumber) {
    std::vector<Package> packages;
    if (!loadPackages(packages)) {
        return false;
    }

    auto it = std::remove_if(packages.begin(), packages.end(),
        [&](const Package& p) { return p.getTrackingNumber() == trackingNumber; });
    
    if (it == packages.end()) {
        return false;
    }

    packages.erase(it, packages.end());

    // 重写文件
    std::ofstream file(databasePath, std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "无法打开数据库文件进行删除！" << std::endl;
        return false;
    }

    for (const auto& p : packages) {
        file << p.toCsvString() << std::endl;
    }
    return true;
}

Package* DatabaseManager::findPackage(const std::string& trackingNumber) {
    std::vector<Package> packages;
    if (!loadPackages(packages)) {
        return nullptr;
    }

    for (auto& p : packages) {
        if (p.getTrackingNumber() == trackingNumber) {
            return &p;
        }
    }
    return nullptr;
}

bool DatabaseManager::savePackages(const std::vector<Package>& packages) {
    std::ofstream file(databasePath, std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "无法打开数据库文件进行写入！" << std::endl;
        return false;
    }

    for (const auto& package : packages) {
        file << package.toCsvString() << std::endl;
    }
    return true;
}

// 实现将在后续添加 