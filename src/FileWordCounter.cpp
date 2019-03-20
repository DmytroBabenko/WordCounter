//
// Created by Dmytro Babenko on 2019-01-25.
//


#include "FileWordCounter.h"
#include "StringWordCounter.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <cmath>


namespace
{
    unsigned long getNumOfSymbolsInFile(std::ifstream& file)
    {
        file.seekg(0, file.end);
        unsigned long length = file.tellg();
        file.seekg(0, file.beg);
        return length;
    }


    bool isAlphabetSymbol(char symbol)
    {
        if (symbol >= 'A' && symbol <= 'z')
            return true;

        return false;
    }
}


FileWordCounter::FileWordCounter(size_t numberOfParallelTasks)
: mNumberOfParallelTasks(numberOfParallelTasks)
, mThreadPool(numberOfParallelTasks)
{
}

FileWordCounter::Result FileWordCounter::countWordsInFile(const std::string &fileName)
{

    std::ifstream file(fileName);
    if (!file)
        throw std::invalid_argument("Cannot read file");

    unsigned long length = getNumOfSymbolsInFile(file);

    unsigned long sizeToRead = static_cast<unsigned long>(ceil((double)length / mNumberOfParallelTasks));


    std::vector<std::future<Result>> futures;


    for (unsigned long startPos = 0; startPos < length; startPos += sizeToRead)
    {
        file.seekg(startPos);
        std::string str(sizeToRead, '\0');
        file.read(&str[0], sizeToRead);

        if (isAlphabetSymbol(str.back()))
        {
            std::string tempStr = findFirstWordInFileFromPos(file, startPos + sizeToRead, length);
            str += tempStr;

            startPos += tempStr.size();
        }

        auto future = mThreadPool.addTaskToAsyncExec(&StringWordCounter::countWordsInStr, str);
        futures.push_back(std::move(future));

    }

    Result wordCountMap = buildWordCountResult(futures);

    return wordCountMap;

}


void FileWordCounter::mergeResult(FileWordCounter::Result& result, FileWordCounter::Result&& tempResult)
{
    for ( auto& item : tempResult)
    {
        auto iter = result.find(item.first);
        if (iter != result.end())
        {
            iter->second += item.second;
        }
        else
        {
            result.insert(std::make_pair(std::move(item.first), item.second));
        }
    }
}

FileWordCounter::Result FileWordCounter::buildWordCountResult(std::vector<std::future<FileWordCounter::Result>>& futures)
{
    if (futures.empty())
        return FileWordCounter::Result();

    auto result = futures[0].get();

    size_t size = futures.size();
    for (size_t i = 1; i < size; ++i)
    {
        auto tempRes = futures[i].get();
        mergeResult(result, std::move(tempRes));
    }

    return result;
}



std::string FileWordCounter::findFirstWordInFileFromPos(std::ifstream &file, size_t start_pos, unsigned long length)
{
    unsigned long leftLength = length - start_pos;

    const size_t chunkSize = 8;

    size_t  pos = start_pos;

    std::string str;

    while (leftLength > 0)
    {
        std::string tempStr(chunkSize, '\0');
        file.seekg(pos);
        file.read(&tempStr[0], chunkSize);


        for (size_t i = 0; i < chunkSize; ++i)
        {
            if (!isAlphabetSymbol(tempStr[i]))
            {
                return str + tempStr.substr(0, i);
            }
        }

        str += tempStr;
        leftLength -= chunkSize;
    }

    return str;
}



