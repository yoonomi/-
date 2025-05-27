#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>
#include <iostream>
#include <vector>
#include <ctime>

class Package {
private:
    std::string trackingNumber;    // 运单号
    std::string recipientName;     // 收件人姓名
    std::string recipientPhone;    // 收件人手机号
    std::string courierCompany;    // 快递公司
    double weight;                 // 重量 (kg)
    std::string category;          // 类别 (如: 文件, 普通, 易碎)
    std::string pickupCode;        // 取件码
    std::string arrivalTime;       // 到达时间 (YYYY-MM-DD HH:MM:SS)
    std::string pickupTime;        // 取件时间 (如果已取)
    bool isPickedUp;              // 是否已取件

public:
    // 默认构造函数
    Package();

    // 设置快件详细信息的函数
    void setDetails(const std::string& tracking, const std::string& name,
                   const std::string& phone, const std::string& company,
                   double pkgWeight, const std::string& pkgCategory);

    // Getters
    std::string getTrackingNumber() const;
    std::string getRecipientName() const;
    std::string getRecipientPhone() const;
    std::string getCourierCompany() const;
    double getWeight() const;
    std::string getCategory() const;
    std::string getPickupCode() const;
    std::string getArrivalTime() const;
    std::string getPickupTime() const;
    bool getIsPickedUp() const;

    // 其他成员函数
    void generatePickupCode(int daily_count);
    void markAsPickedUp();
    void displayDetails() const;
    std::string toCsvString() const;
    void fromCsvString(const std::string& csv_line);
};

#endif // PACKAGE_H 