cmake_minimum_required(VERSION 3.10)
project(Logger)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(logger 
    src/main.cpp 
    src/Logger.cpp
)

# GoogleTest
enable_testing()
find_package(GTest REQUIRED)

add_executable(runTests
    tests/test_logger.cpp
    src/Logger.cpp
)

target_link_libraries(runTests
    GTest::GTest
    GTest::Main
    pthread
)

add_test(NAME LoggerTests COMMAND runTests)

