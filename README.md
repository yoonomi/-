# 快件管理系统

一个基于 C++ 的快件管理系统，支持快件的录入、修改、删除、查询和统计等功能。

## 功能特点

- 服务人员功能
  - 快件录入
  - 快件修改
  - 快件删除
  - 快件查询
  - 统计信息（按时间段/快递公司）

- 收件人功能
  - 快件查询
  - 取件（支持取件码/手机号/运单号）

## 系统要求

- Windows 操作系统
- MinGW-w64 或 TDM-GCC 编译器
- C++14 或更高版本

## 编译和运行

### 方法一：使用批处理文件

1. 双击 `build.bat` 文件
2. 等待编译完成
3. 程序将自动运行

### 方法二：手动编译

```bash
g++ -std=c++14 -Wall -Wextra main.cpp Package.cpp DatabaseManager.cpp SystemManager.cpp utils.cpp -o express_system
```

### 方法三：使用 VS Code

1. 安装 C/C++ 扩展
2. 按 `Ctrl+Shift+B` 编译
3. 按 `F5` 运行

## 使用说明

1. 运行程序后，选择服务人员登录或收件人服务
2. 服务人员默认密码：123456
3. 按照菜单提示进行操作

## 文件结构

- `main.cpp` - 主程序入口
- `Package.h/cpp` - 快件类定义和实现
- `DatabaseManager.h/cpp` - 数据库管理类
- `SystemManager.h/cpp` - 系统管理类
- `utils.h/cpp` - 工具函数
- `build.bat` - 编译脚本

## 注意事项

- 数据保存在 `packages.csv` 文件中
- 请确保程序有写入权限
- 建议定期备份数据文件 