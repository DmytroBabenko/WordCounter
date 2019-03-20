//
// Created by Dmytro Babenko on 2019-01-31.
//
#include <gtest/gtest.h>
#include "../ThreadPool/ThreadPool.h"

#include <iostream>


class ThreadPoolTest : public ::testing::Test {
public:
    ThreadPoolTest() = default;
    ~ThreadPoolTest() override = default;
    void SetUp() override { /* called before every test */ }
    void TearDown() override { /* called after every test */ }

protected:
    /* none yet */
};

//TEST_F(ThreadPoolTest, runTwoTasksSynchronously)
//{
//    ThreadPool threadPool(1);
//
//    auto five_second = std::chrono::seconds(5);
//    auto start = std::chrono::steady_clock::now();
//
//    auto future1 = threadPool.addTaskToAsyncExec([=]()
//                                  {
//                                      std::this_thread::sleep_for(five_second);
//                                  });
//
//    auto future2 = threadPool.addTaskToAsyncExec([=]()
//                                  {
//                                      std::this_thread::sleep_for(five_second);
//                                  });
//
//    future1.get();
//    future2.get();
//
//
//
//    auto end = std::chrono::steady_clock::now();
//
//    auto diff = std::chrono::duration_cast<std::chrono::seconds>(end - start);
//
//    ASSERT_TRUE(diff >= 2 * five_second);
//
//}
//

TEST_F(ThreadPoolTest, runTwoTasksAsynchronously)
{
    ThreadPool threadPool(2);

    auto five_second = std::chrono::seconds(5);
    auto start = std::chrono::steady_clock::now();

    auto future1 = threadPool.addTaskToAsyncExec([=]()
                                                 {
                                                     std::this_thread::sleep_for(five_second);
                                                 });

    auto future2 = threadPool.addTaskToAsyncExec([=]()
                                                 {
                                                     std::this_thread::sleep_for(five_second);
                                                 });

    future1.get();
    future2.get();



    auto end = std::chrono::steady_clock::now();

    auto diff = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    ASSERT_TRUE(diff < 2 * five_second);

}