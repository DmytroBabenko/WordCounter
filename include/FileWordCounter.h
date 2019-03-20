//
// Created by Dmytro Babenko on 2019-01-25.
//

#ifndef WORDCOUNTER_WORDCOUNTER_H
#define WORDCOUNTER_WORDCOUNTER_H

#include <map>

#include "ThreadPool.h"

class FileWordCounter
{
public:
    typedef std::map<std::string, long> Result;
public:
    explicit FileWordCounter(size_t numberOfParallelTasks);

    Result countWordsInFile(const std::string& fileName);

private:
    void mergeResult(FileWordCounter::Result& result, FileWordCounter::Result&& tempResult);
    Result buildWordCountResult(std::vector<std::future<FileWordCounter::Result>>& futures);
    std::string findFirstWordInFileFromPos(std::ifstream& file, size_t start_pos, unsigned long length);

private:
    const size_t mNumberOfParallelTasks;
    ThreadPool mThreadPool;
};
#endif //WORDCOUNTER_WORDCOUNTER_H
