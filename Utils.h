#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

std::vector<std::string> ReadWordsFromFile(const std::string& fileName);
int CountWordsInFile(const std::vector<std::string>& words, char letter);

#endif // UTILS_H
