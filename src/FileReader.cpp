#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <memory>
#include <utility>
#include "WordDao.h"
#include "FileReader.h"

FileReader::FileReader(std::string fileName, std::shared_ptr<WordDAO> wordDAO)
        : fileName(std::move(fileName)), wordDAO(std::move(wordDAO)) {
}

void FileReader::readAndStore() const {
        std::ifstream file(fileName);
        if (!file.is_open()) {
                std::cout << "Error: Could not open the file! " << fileName << std::endl;
                return;
        }

        std::string word;
        std::unordered_set<std::string> words;
        while (std::getline(file, word)) {
                words.insert(word);
        }
        if (!words.empty()) {
                wordDAO->emptyTable();
                for (const auto& each_word : words) {
                        wordDAO->addWord(each_word);
                }
                std::cout << "Words stored! " << fileName << std::endl;
        } else {
                std::cout << "Empty file! " << fileName << std::endl;
        }

        file.close();
}