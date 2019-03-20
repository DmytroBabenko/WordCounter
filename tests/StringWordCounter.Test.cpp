//
// Created by Dmytro Babenko on 2019-03-19.
//

#include <gtest/gtest.h>
#include <StringWordCounter.h>


class StringWordCounterTest : public ::testing::Test {
public:
    StringWordCounterTest() = default;
    ~StringWordCounterTest() override = default;
    void SetUp() override { /* called before every test */ }
    void TearDown() override { /* called after every test */ }

protected:
    /* none yet */
};


TEST_F(StringWordCounterTest, countWordsInStrTest)
{
    const std::string str = "Cat Dog cat Cat dog Dog dOg";

    std::map<std::string, long> wordCountMap = StringWordCounter::countWordsInStr(str);

    auto catIter = wordCountMap.find("cat");
    ASSERT_FALSE(catIter == wordCountMap.end());
    ASSERT_EQ(3, catIter->second);

    auto dogIter = wordCountMap.find("dog");
    ASSERT_FALSE(dogIter == wordCountMap.end());
    ASSERT_EQ(4, dogIter->second);
}
