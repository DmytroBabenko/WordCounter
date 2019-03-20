//
// Created by Dmytro Babenko on 2019-03-19.
//

#ifndef WORDCOUNTER_STRINGWORDCOUNTER_H
#define WORDCOUNTER_STRINGWORDCOUNTER_H

#include <map>
#include <regex>


class StringWordCounter
{
public:
    typedef std::map<std::string, long> Result;

public:
    static Result countWordsInStr(const std::string& str);

private:
    static std::regex mRegex;
};

#endif //WORDCOUNTER_STRINGWORDCOUNTER_H
