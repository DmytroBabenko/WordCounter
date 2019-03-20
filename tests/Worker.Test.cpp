//
// Created by Dmytro Babenko on 2019-01-31.
//

#include <gtest/gtest.h>
#include "../ThreadPool/Worker.h"


class WorkerTest : public ::testing::Test {
public:
    WorkerTest() = default;
    ~WorkerTest() override = default;
    void SetUp() override { /* called before every test */ }
    void TearDown() override { /* called after every test */ }

protected:
    /* none yet */
};


TEST_F(WorkerTest, simpleTask)
{
    Worker worker;


    auto sum = [](int a, int b)
    {
        return a + b;
    };

    auto future = worker.addTask(sum, 2, 3);

    int res = future.get();

    ASSERT_EQ(5, res);
}

TEST_F(WorkerTest, isFree)
{
    Worker worker;

    ASSERT_TRUE(worker.isFree());

    auto sum = [](int a, int b)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        return a + b;
    };

    auto future = worker.addTask(sum, 2, 3);

    ASSERT_FALSE(worker.isFree());

    future.get();

    ASSERT_TRUE(worker.isFree());
}


TEST_F(WorkerTest, getNumberOfTasks)
{
    Worker worker;

    ASSERT_EQ(0, worker.getNumberOfTasks());


    auto sum = [](int a, int b)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        return a + b;
    };

    auto future = worker.addTask(sum, 2, 3);

    ASSERT_EQ(1, worker.getNumberOfTasks());


    future.get();

    ASSERT_EQ(0, worker.getNumberOfTasks());
}


TEST_F(WorkerTest, twoTasks)
{
    Worker worker;

    auto sum2 = [](int a, int b)
    {
        return a + b;
    };
    auto future2 = worker.addTask(sum2, 2, 3);

    auto sum3 = [](int a, int b, int c)
    {
        return a + b + c;
    };
    auto future3 = worker.addTask(sum3, 1, 2, 3);

    int res = future2.get() + future3.get();
    ASSERT_EQ(11, res);

}

TEST_F(WorkerTest, exception)
{
    Worker worker;

    auto fun = []()
    {
        throw std::exception();
    };

    auto future = worker.addTask(fun);

    ASSERT_THROW(future.get(), std::exception);
}


TEST_F(WorkerTest, execAssClassMethod)
{
    Worker worker;

    class A
    {
    public:
        int sum(int a, int b)
        {
            return a + b;
        }
    };

    auto future = worker.addTask(&A::sum, A(), 1, 2);

    ASSERT_EQ(3, future.get());
}

