//
// Created by dbabenko on 19.03.19.
//


#include "ConfigParameters.h"

#include <fstream>


namespace
{
    std::string trimSpace(const std::string& str)
    {
        size_t first = str.find_first_not_of(' ');
        if (first == std::string::npos)
        {
            return str;
        }
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }
}

ConfigParameters::ConfigParameters(const std::string& iInputFile,
             size_t iNumThreads,
             const std::string& iOutFileAlphabetOrder,
             const std::string& iOutFileCountOrder)
        : inputFile(iInputFile)
        , numThreads(iNumThreads)
        , outFileAlphabetOrder(iOutFileAlphabetOrder)
        , outFileCountOrder(iOutFileCountOrder)
        , useDir(false)
{

}

ConfigParameters::ConfigParameters(const std::string& iDirectory,
                                   size_t iNumThreads,
                                   const std::string& iOutFileAlphabetOrder,
                                   const std::string& iOutFileCountOrder,
                                   const std::string& extension)
        : inputDirectory(iDirectory)
        , numThreads(iNumThreads)
        , outFileAlphabetOrder(iOutFileAlphabetOrder)
        , outFileCountOrder(iOutFileCountOrder)
        , extension(extension)
        , useDir(true)
{
}

ConfigParameters ConfigParameters::parseConfig(const std::string configFile)
{
    std::ifstream file(configFile);

    if (!file)
        throw std::invalid_argument("No config file");

    std::string inputFile, inputDir, outFileAlphabetOrder, outFileCountOrder, extension;
    bool use_dir = false;
    size_t numThreads = 1;

    std::string line;
    while (getline(file, line))
    {
        size_t pos = line.find('=');

        if (line.find("use_dir") != std::string::npos)
            use_dir = static_cast<bool>(std::stoi(line.substr(pos + 1)));

        if (line.find("input_file") != std::string::npos)
            inputFile = trimSpace(line.substr(pos + 1));

        if (line.find("input_dir") != std::string::npos)
            inputDir = trimSpace(line.substr(pos + 1));


        if (line.find("output_file_alphabet_order") != std::string::npos)
            outFileAlphabetOrder = trimSpace(line.substr(pos + 1));

        if (line.find("output_file_count_order") != std::string::npos)
            outFileCountOrder = trimSpace(line.substr(pos + 1));

        if (line.find("extension") != std::string::npos)
            extension = trimSpace(line.substr(pos + 1));

        if (line.find("num_threads") != std::string::npos)
            numThreads = std::stoi(line.substr(pos + 1));
    }

    if (inputFile.empty() || outFileCountOrder.empty() || outFileAlphabetOrder.empty())
        std::invalid_argument("Cannot parse input parameters from config file");


    if (use_dir)
        return ConfigParameters(inputDir, numThreads, outFileAlphabetOrder, outFileCountOrder, extension);

    return ConfigParameters(inputFile, numThreads, outFileAlphabetOrder, outFileCountOrder);


}