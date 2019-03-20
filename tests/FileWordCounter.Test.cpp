//
// Created by Dmytro Babenko on 2019-01-25.
//
#include <gtest/gtest.h>
#include <FileWordCounter.h>


class WordCounterTest : public ::testing::Test {
public:
    WordCounterTest() = default;
    ~WordCounterTest() override = default;
    void SetUp() override { /* called before every test */ }
    void TearDown() override { /* called after every test */ }

protected:
    /* none yet */
};


// test case when one word is splitted into two theare=th+eare
//one thread calc it like th, another like eare
TEST_F(WordCounterTest, countWordsInFileSplitWord)
{
    const std::string file = "../data/test.txt";

    FileWordCounter wordCounter(8);

    std::map<std::string, long> wordCountMap = wordCounter.countWordsInFile(file);


    ASSERT_EQ(20, wordCountMap["there"]);
    ASSERT_EQ(20, wordCountMap["are"]);
    ASSERT_EQ(20, wordCountMap["a"]);
    ASSERT_EQ(20, wordCountMap["lot"]);
    ASSERT_EQ(40, wordCountMap["of"]);
    ASSERT_EQ(20, wordCountMap["words"]);
    ASSERT_EQ(20, wordCountMap["in"]);
    ASSERT_EQ(20, wordCountMap["this"]);
    ASSERT_EQ(20, wordCountMap["file"]);
    ASSERT_EQ(20, wordCountMap["course"]);
}


// test case when one word is splitted into two theare=th+eare
//one thread calc it like th, another like eare
//TEST_F(WordCounterTest, countWordsInBigFile)
//{
//    const std::string file = "../data/big.txt";
//
//    FileWordCounter wordCounter(1);
//
//    std::map<std::string, long> wordCountMap = wordCounter.countWordsInFile(file);
//}
