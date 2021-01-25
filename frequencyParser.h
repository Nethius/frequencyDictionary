//
// Created by Developer on 25.01.2021.
//

#ifndef FREQ_FREQUENCYPARSER_H
#define FREQ_FREQUENCYPARSER_H

#include <map>
#include <string>
#include <vector>
#include <fstream>

namespace freq {
    /*!
     * Sorted dictionary first by frequency, then alphabetically. Then writes to the output stream
     * @param map - with words and frequent use, sorted alphabetically
     * @param stream - output stream
     */
    void saveSortedDictionary(const std::map<std::string, size_t> &map, std::ostream &stream);

    /*!
     * Parse input stream in map<word, frequent use>
     * @param stream - input stream
     * @return map<word, frequent use>
     */
    std::map<std::string, size_t> parse(std::istream &stream);
}
#endif //FREQ_FREQUENCYPARSER_H
