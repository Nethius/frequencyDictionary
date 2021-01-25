//
// Created by Developer on 25.01.2021.
//

#include "frequencyParser.h"
#include <algorithm>
#include <iostream>

namespace freq {
    bool isASCII(const char c) {
        return 0 <= c && c <= 127; // a-zA-Z stored in the lower 7 bits of a char (values 0-127)
    }

    std::map<std::string, size_t> parse(std::istream &stream) {

        std::map<std::string, size_t> wordsCount;
        std::string word;

        if (!stream.good()) {
            std::cout << "error occurred in input stream" << std::endl;
            return wordsCount;
        }

        std::string str(std::istreambuf_iterator<char>(stream), {});

        for (auto it = str.begin(); it < str.end(); it++) {
            bool wordFound = false;

            if (isASCII(*it) && (!std::isspace(*it) || std::ispunct(*it))) {
                if (std::isalpha(*it))
                    word.push_back(std::tolower(*it));
            } else {
                wordFound = true;
            }

            if ((wordFound || it + 1 == str.end()) && !word.empty()) {
                auto mapIt = wordsCount.find(word);
                size_t count = 1;
                if (mapIt != wordsCount.end())
                    count = ++mapIt->second;

                wordsCount.insert_or_assign(word, count);
                word.clear();
                wordFound = false;
            }
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

    void saveSortedDictionary(const std::map<std::string, size_t> &map, std::ostream &stream) {
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