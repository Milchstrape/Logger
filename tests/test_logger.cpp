#include "Logger.h"
#include <gtest/gtest.h>
#include <fstream>
#include <thread>

// 测试基础日志功能
TEST(LoggerTest, BasicLogging) {
    Logger& logger = Logger::getInstance();
    logger.setLogFile("test.log");
    logger.start();

    logger.log(Logger::INFO, "单元测试日志");
    logger.stop();

    std::ifstream file("test.log");
    std::string line;
    bool found = false;
    while (std::getline(file, line)) {
        if (line.find("单元测试日志") != std::string::npos) {
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);
}

// 测试多线程并发日志
TEST(LoggerTest, MultiThreadLogging) {
    Logger& logger = Logger::getInstance();
    logger.setLogFile("test_mt.log");
    logger.start();

    auto worker = [&logger](int id) {
        for (int i = 0; i < 10; i++) {
            logger.log(Logger::INFO, "线程 " + std::to_string(id) + " 日志 " + std::to_string(i));
        }
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < 4; i++) {
        threads.emplace_back(worker, i);
    }

    for (auto& t : threads) t.join();

    logger.stop();

    std::ifstream file("test_mt.log");
    int lineCount = 0;
    std::string line;
    while (std::getline(file, line)) {
        lineCount++;
    }

    // 4 个线程 * 10 条日志 = 40 条
    EXPECT_GE(lineCount, 40);
}

