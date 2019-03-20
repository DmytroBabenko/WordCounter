//
// Created by dbabenko on 19.03.19.
//

#ifndef WORDCOUNTER_RESULTSAVER_H
#define WORDCOUNTER_RESULTSAVER_H

#include <string>
#include "FileWordCounter.h"

class ResultSaver
{
public:
    static void saveToFileInAlphabeticOrder(const FileWordCounter::Result& wordCountMap ,const std::string& file);
    static void saveToFileInCountOrder(const FileWordCounter::Result& wordCountMap ,const std::string& file);

};

#endif //WORDCOUNTER_RESULTSAVER_H
