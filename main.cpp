#include <iostream>



#include "FileWordCounter.h"
#include "ConfigParameters.h"
#include "ResultSaver.h"




int main(int argc, char** argv) {

    if (argc != 2) {
        std::cerr << "Invalid number of input parameters" << std::endl;
        return 1;
    }


    const std::string configFile = argv[1];

    ConfigParameters configParameters = ConfigParameters::parseConfig(configFile);




    auto start = std::chrono::system_clock::now();

    FileWordCounter fileWordCounter(std::thread::hardware_concurrency());
    auto wordCountMap = fileWordCounter.countWordsInFile(configParameters.inputFile);

    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Counting time: " <<elapsed.count() << " ms"<<std::endl;

    start = std::chrono::system_clock::now();
    ResultSaver::saveToFileInAlphabeticOrder(wordCountMap, configParameters.outFileAlphabetOrder);
    ResultSaver::saveToFileInCountOrder(wordCountMap, configParameters.outFileCountOrder);
    end = std::chrono::system_clock::now();
    std::cout << "Writing result time: " <<elapsed.count() << " ms"<<std::endl;

    return 0;


//    testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();

}