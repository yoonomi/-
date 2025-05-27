#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <string>
#include <vector>
#include "Package.h"

class DatabaseManager {
private:
    std::string databasePath;

public:
    DatabaseManager(const std::string& path);
    bool savePackage(const Package& package);
    bool savePackages(const std::vector<Package>& packages);
    bool loadPackages(std::vector<Package>& packages);
    bool updatePackage(const Package& package);
    bool deletePackage(const std::string& trackingNumber);
    Package* findPackage(const std::string& trackingNumber);
};

#endif // DATABASE_MANAGER_H 