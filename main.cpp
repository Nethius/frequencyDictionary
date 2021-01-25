#include <iostream>
#include <fstream>
#include "frequencyParser.h"

const size_t availableKeysCount = 3;

int main(int argc, char *argv[]) {
    try {
        if (argc == availableKeysCount) {
            std::string inputFile = argv[1];
            std::string outputFile = argv[2];

            std::fstream inputStream;
            inputStream.open(inputFile, std::fstream::in);

            auto map = freq::parse(inputStream);

            std::fstream outputStream;
            outputStream.open(outputFile, std::fstream::out);

            freq::saveSortedDictionary(map, outputStream);
            return 0;
        } else {
            std::cout << "wrong command line keys" << std::endl;
            std::cout << "example of use: freq in.txt out.txt" << std::endl;
            return 0;
        }
    }
    catch (...) {
        std::cout << "Unhandled exception caught. The application will be closed" << std::endl;
        return 0;
    }
}
