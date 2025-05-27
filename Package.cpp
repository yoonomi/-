#include "Package.h"
#include <sstream>
#include <iomanip>
#include "utils.h"

// 构造函数
Package::Package() : weight(0.0), isPickedUp(false) {}

// 设置快件详细信息
void Package::setDetails(const std::string& tracking, const std::string& name,
                        const std::string& phone, const std::string& company,
                        double pkgWeight, const std::string& pkgCategory) {
    trackingNumber = tracking;
    recipientName = name;
    recipientPhone = phone;
    courierCompany = company;
    weight = pkgWeight;
    category = pkgCategory;
    arrivalTime = Utils::getCurrentTimeString();
    isPickedUp = false;
    pickupTime = "";
}

// Getters
std::string Package::getTrackingNumber() const { return trackingNumber; }
std::string Package::getRecipientName() const { return recipientName; }
std::string Package::getRecipientPhone() const { return recipientPhone; }
std::string Package::getCourierCompany() const { return courierCompany; }
double Package::getWeight() const { return weight; }
std::string Package::getCategory() const { return category; }
std::string Package::getPickupCode() const { return pickupCode; }
std::string Package::getArrivalTime() const { return arrivalTime; }
std::string Package::getPickupTime() const { return pickupTime; }
bool Package::getIsPickedUp() const { return isPickedUp; }

// 生成取件码
void Package::generatePickupCode(int daily_count) {
    std::stringstream ss;
    ss << std::setw(3) << std::setfill('0') << daily_count;
    pickupCode = Utils::getCurrentDateString().substr(5, 2) + ss.str();
}

// 标记为已取件
void Package::markAsPickedUp() {
    isPickedUp = true;
    pickupTime = Utils::getCurrentTimeString();
}

// 显示快件详情
void Package::displayDetails() const {
    std::cout << "运单号: " << trackingNumber << std::endl;
    std::cout << "收件人: " << recipientName << std::endl;
    std::cout << "手机号: " << recipientPhone << std::endl;
    std::cout << "快递公司: " << courierCompany << std::endl;
    std::cout << "重量: " << weight << "kg" << std::endl;
    std::cout << "类别: " << category << std::endl;
    std::cout << "取件码: " << pickupCode << std::endl;
    std::cout << "到达时间: " << arrivalTime << std::endl;
    if (isPickedUp) {
        std::cout << "取件时间: " << pickupTime << std::endl;
    }
    std::cout << "状态: " << (isPickedUp ? "已取件" : "待取件") << std::endl;
}

// 转换为CSV字符串
std::string Package::toCsvString() const {
    std::stringstream ss;
    ss << trackingNumber << ","
       << recipientName << ","
       << recipientPhone << ","
       << courierCompany << ","
       << weight << ","
       << category << ","
       << pickupCode << ","
       << arrivalTime << ","
       << pickupTime << ","
       << (isPickedUp ? "1" : "0");
    return ss.str();
}

// 从CSV字符串解析
void Package::fromCsvString(const std::string& csv_line) {
    std::stringstream ss(csv_line);
    std::string item;
    
    // 使用getline分割CSV
    std::getline(ss, trackingNumber, ',');
    std::getline(ss, recipientName, ',');
    std::getline(ss, recipientPhone, ',');
    std::getline(ss, courierCompany, ',');
    
    std::getline(ss, item, ',');
    weight = std::stod(item);
    
    std::getline(ss, category, ',');
    std::getline(ss, pickupCode, ',');
    std::getline(ss, arrivalTime, ',');
    std::getline(ss, pickupTime, ',');
    
    std::getline(ss, item, ',');
    isPickedUp = (item == "1");
}

// 实现将在后续添加 