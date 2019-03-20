cmake_minimum_required(VERSION 3.13)
project(WordCounter)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)

include_directories(
        include
        ThreadPool
        ${GTEST_INCLUDE_DIRS}
)


add_executable(${PROJECT_NAME} main.cpp src/FileWordCounter.cpp tests/FileWordCounter.Test.cpp ThreadPool/ThreadPool.h ThreadPool/ThreadPool.cpp ThreadPool/Worker.h ThreadPool/Worker.cpp tests/Worker.Test.cpp tests/ThreadPool.Test.cpp include/StringWordCounter.h src/StringWordCounter.cpp tests/StringWordCounter.Test.cpp include/ConfigParameters.h src/ConfigParameters.cpp include/ResultSaver.h src/ResultSaver.cpp)

target_link_libraries(
        ${PROJECT_NAME} ${GTEST_LIBRARIES}
        pthread)


enable_testing()
add_test(${PROJECT_NAME} "./WordCounter.Test")