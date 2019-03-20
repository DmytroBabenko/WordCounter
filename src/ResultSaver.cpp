//
// Created by dbabenko on 19.03.19.
//

#include "ResultSaver.h"

#include <fstream>
#include <algorithm>


void ResultSaver::saveToFileInAlphabeticOrder(const FileWordCounter::Result &wordCountMap, const std::string &file)
{
    std::ofstream ofstreamFile(file);
    for (const auto& item : wordCountMap)
    {
        ofstreamFile << item.first<< " - " <<item.second<<std::endl;
    }
}


void ResultSaver::saveToFileInCountOrder(const FileWordCounter::Result &wordCountMap, const std::string &file)
{

    std::multimap<long, std::string> flipedWordCountMap;
    std::transform(wordCountMap.cbegin(), wordCountMap.cend(), std::inserter(flipedWordCountMap, flipedWordCountMap.begin()),
            [&](const std::pair<std::string, long> item)
            {
                return std::make_pair(item.second, item.first);
            });

    std::ofstream ofstreamFile(file);
    for (const auto& item : flipedWordCountMap)
    {
        ofstreamFile << item.second<< " - " <<item.first<<std::endl;
    }

}