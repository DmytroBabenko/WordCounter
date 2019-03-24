//
// Created by dbabenko on 19.03.19.
//

#ifndef WORDCOUNTER_CONFIGPARAMETERS_H
#define WORDCOUNTER_CONFIGPARAMETERS_H

#include <string>

struct ConfigParameters
{

    ConfigParameters(const std::string& iInputFile,
                 size_t iNumThreads,
                 const std::string& iOutFileAlphabetOrder,
                 const std::string& iOutFileCountOrder);

    ConfigParameters(const std::string& iDirectory,
                     size_t iNumThreads,
                     const std::string& iOutFileAlphabetOrder,
                     const std::string& iOutFileCountOrder,
                     const std::string& iExtension);

    static ConfigParameters parseConfig(const std::string configFile);
    std::string inputFile;
    std::string inputDirectory;
    size_t numThreads;
    std::string outFileAlphabetOrder;
    std::string outFileCountOrder;
    std::string extension;
    bool useDir;
};


#endif //WORDCOUNTER_CONFIGPARAMETERS_H
