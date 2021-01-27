//
// Created by Developer on 25.01.2021.
//

#include "frequencyParser.h"
#include <algorithm>
#include <iostream>
#include <chrono>

namespace freq {
    std::unordered_map<std::string, size_t> parse(std::istream &stream) {
        auto start = std::chrono::high_resolution_clock::now();
        std::string const symbols{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
        std::unordered_map<std::string, size_t> wordsCount;
        std::string word;

        if (!stream.good()) {
            std::cout << "error occurred in input stream" << std::endl;
            return wordsCount;
        }

        std::string str(std::istreambuf_iterator<char>(stream), {});
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "stream to string: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;
        start = std::chrono::high_resolution_clock::now();
        size_t beg, pos = 0;
        while ((beg = str.find_first_of(symbols, pos)) != std::string::npos) {
            pos = str.find_first_not_of(symbols, beg + 1);
            word = str.substr(beg, pos - beg);
            std::transform(word.begin(), word.end(), word.begin(), std::tolower);

            auto mapIt = wordsCount.find(word);
            size_t count = 1;
            if (mapIt != wordsCount.end())
                count = ++mapIt->second;

            wordsCount.insert_or_assign(word, count);
            word.clear();
        }
        end = std::chrono::high_resolution_clock::now();
        std::cout << "string to words: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;
        return wordsCount;
    }

    struct comparator {
        bool operator()(const std::pair<std::string, size_t> &l, const std::pair<std::string, size_t> &r) const {
            if (l.second == r.second)
                return l.first < r.first;
            return l.second > r.second;
        }
    };

    void saveSortedDictionary(const std::unordered_map<std::string, size_t> &map, std::ostream &stream) {
        auto start = std::chrono::high_resolution_clock::now();
        if (!stream.good()) {
            std::cout << "error occurred in output stream" << std::endl;
            return;
        }
        if (map.empty()) {
            std::cout << "the dictionary is empty, nothing to write" << std::endl;
            return;
        }
        std::vector<std::pair<std::string, size_t>> v(map.begin(), map.end());
        std::sort(v.begin(), v.end(), comparator());

        for (const auto &i : v) {
            stream << i.second << " " << i.first << std::endl;
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "words to stream: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;
    }
}