# C++ 异步日志系统

## 📌 项目简介
## 本项目实现了一个基于 **C++17** 的高性能异步日志库，支持多线程并发写日志，采用 **生产者-消费者模型** 设计。日志同时输出到控制台与文件，适合后端服务中的日志记录场景。

## ✨ 功能特性
- **异步日志**：日志先进队列，由后台线程统一写文件，避免阻塞。
- **线程安全**：使用 `std::mutex` + `std::condition_variable` 保证并发安全。
- **日志级别**：支持 `INFO` / `WARNING` / `ERROR`。
- **双输出**：控制台和文件同时输出。
- **单元测试**：基于 **GoogleTest**，覆盖并发场景，100% 通过。

## 🏗️ 项目结构
Logger/
│── include/ # 头文件

│ └── Logger.h

│── src/ # 源码

│ ├── Logger.cpp

│ └── main.cpp

│── tests/ # 单元测试

│ └── test_logger.cpp

│── CMakeLists.txt # 构建配置

│── README.md # 项目说明

│── build/ # 编译输出目录

## 🚀 快速开始

### 1. 编译
```bash
cd build
cmake ..
make
```
### 运行 Demo
```bash
./logger
```
## 运行单元测试
```bash
ctest
```

## 技术要点

C++17

CMake 构建

GoogleTest 单元测试

线程同步（mutex, condition_variable）

异步队列模型



