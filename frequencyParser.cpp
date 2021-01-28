//
// Created by Developer on 25.01.2021.
//

#include "frequencyParser.h"
#include <cctype>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>

namespace freq {
    std::unordered_map<std::string, size_t> parse(std::istream &stream) {
        std::string const symbols{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
        std::unordered_map<std::string, size_t> wordsCount;
        std::string word;

        if (!stream.good()) {
            std::cout << "error occurred in input stream" << std::endl;
            return wordsCount;
        }

        std::string str(std::istreambuf_iterator<char>(stream), {});
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
    }
}