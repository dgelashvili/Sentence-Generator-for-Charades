#ifndef FILEREADER_H
#define FILEREADER_H

#include <memory>
#include <string>
#include "WordDao.h"

/**
 * @class FileReader
 * @brief Reads words from a file and stores them in a database via a DAO object.
 *
 * The FileReader class is responsible for reading the contents of a file specified by the file name,
 * extracting individual words, and storing them in a database using the provided WordDAO object.
 * This class ensures that all words in the file are saved efficiently and can later be retrieved
 * via the DAO for use in the application.
 */
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
