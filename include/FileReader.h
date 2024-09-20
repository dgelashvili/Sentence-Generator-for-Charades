#ifndef FILEREADER_H
#define FILEREADER_H

#include <memory>
#include <string>
#include "WordDao.h"

class FileReader {
public:
    FileReader(std::string fileName, std::shared_ptr<WordDAO> wordDAO);
    ~FileReader() = default;

    void readAndStore() const;
private:
    std::string fileName;
    std::shared_ptr<WordDAO> wordDAO;
};

#endif //FILEREADER_H
