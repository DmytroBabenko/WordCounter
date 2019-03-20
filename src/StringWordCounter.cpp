//
// Created by Dmytro Babenko on 2019-03-19.
//

#include "StringWordCounter.h"

namespace
{
    void strToLowerCase(std::string &str)
    {
        std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c)
        {
            return std::tolower(c);
        });
    }
}

std::regex StringWordCounter::mRegex("\\w+");

StringWordCounter::Result StringWordCounter::countWordsInStr(const std::string &str)
{
    StringWordCounter::Result wordCountMap;

    for( std::sregex_iterator it(str.begin(), str.end(), mRegex), it_end; it != it_end; ++it )
    {
        std::string word = (*it)[0];
        strToLowerCase(word);
        auto iterWord = wordCountMap.find(word);
        if (iterWord == wordCountMap.end())
        {
            wordCountMap[std::move(word)] = 1;
        }
        else
        {
            ++wordCountMap[word];
        }
    }

    return wordCountMap;


}
