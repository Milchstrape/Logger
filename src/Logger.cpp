#include "Logger.h"

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

Logger::Logger() : running(false) {}

Logger::~Logger() {
    stop();
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::setLogFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(mtx);
    if (logFile.is_open()) {
        logFile.close();
    }
    logFile.open(filename, std::ios::app);
}

void Logger::start() {
    running = true;
    worker = std::thread(&Logger::workerThread, this);
}

void Logger::stop() {
    running = false;
    cv.notify_all();
    if (worker.joinable()) {
        worker.join();
    }
}

void Logger::log(Level level, const std::string& message) {
    std::string logMsg = getTimeStamp() + " [" + levelToString(level) + "] " + message;

    {
        std::lock_guard<std::mutex> lock(mtx);
        logQueue.push(logMsg);
    }
    cv.notify_one();  // 通知后台线程
}

void Logger::workerThread() {
    while (running || !logQueue.empty()) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return !logQueue.empty() || !running; });

        while (!logQueue.empty()) {
            std::string msg = logQueue.front();
            logQueue.pop();
            lock.unlock();

            // 输出到控制台
            std::cout << msg << std::endl;

            // 写入文件
            if (logFile.is_open()) {
                logFile << msg << std::endl;
            }

            lock.lock();
        }
    }
}

std::string Logger::levelToString(Level level) {
    switch (level) {
        case INFO: return "INFO";
        case WARNING: return "WARNING";
        case ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

std::string Logger::getTimeStamp() {
    std::time_t now = std::time(nullptr);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return buf;
}

