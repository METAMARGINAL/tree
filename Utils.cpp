#include "Utils.h"
#include <fstream>
#include <iostream>

std::vector<std::string> ReadWordsFromFile(const std::string& fileName) {
    std::vector<std::string> words;
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        return words;
    }

    std::string word;
    while (file >> word) {
        words.push_back(word);
    }

    file.close();
    return words;
}

int CountWordsInFile(const std::vector<std::string>& words, char letter) {
    int count = 0;
    for (const auto& word : words) {
        if (!word.empty() && word[0] == letter) {
            count++;
        }
    }
    return count;
}
