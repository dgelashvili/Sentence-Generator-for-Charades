#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
        std::vector<std::string> words;
        while (std::getline(file, word)) {
                words.push_back(word);
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