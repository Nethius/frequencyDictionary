#include <iostream>
#include <fstream>
#include "frequencyParser.h"
#include <chrono>

const size_t availableKeysCount = 3;

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
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

            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Time from start: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;
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
