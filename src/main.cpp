#include "Logger.h"
#include <thread>
#include <vector>

void worker(int id) {
    Logger& logger = Logger::getInstance();
    for (int i = 0; i < 5; i++) {
        logger.log(Logger::INFO, "线程 " + std::to_string(id) + " 输出日志 " + std::to_string(i));
    }
}

int main() {
    Logger& logger = Logger::getInstance();
    logger.setLogFile("app.log");
    logger.start();

    logger.log(Logger::INFO, "主线程启动");

    std::vector<std::thread> threads;
    for (int i = 0; i < 4; i++) {
        threads.emplace_back(worker, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    logger.log(Logger::INFO, "所有线程完成");

    logger.stop();  // 停止后台线程，保证队列清空

    return 0;
}

