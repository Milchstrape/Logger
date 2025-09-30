#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <mutex>
#include <ctime>
#include <queue>
#include <thread>
#include <condition_variable>
#include <atomic>

class Logger {
public:
    enum Level { INFO, WARNING, ERROR };

    static Logger& getInstance();

    void setLogFile(const std::string& filename);
    void log(Level level, const std::string& message);

    void start();   // 启动后台线程
    void stop();    // 停止后台线程

private:
    Logger();
    ~Logger();

    void workerThread();  // 后台线程执行的函数
    std::string levelToString(Level level);
    std::string getTimeStamp();

    std::ofstream logFile;
    std::mutex mtx;
    std::condition_variable cv;
    std::queue<std::string> logQueue;

    std::thread worker;
    std::atomic<bool> running;
};

#endif // LOGGER_H

