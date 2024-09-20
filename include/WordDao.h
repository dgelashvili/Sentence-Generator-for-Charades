#ifndef WORDDAO_H
#define WORDDAO_H

#include <string>
#include "sqlite3.h"

class WordDAO {
public:
    WordDAO(const std::string& dbPath, const std::string& tableName);
    ~WordDAO();

    void addWord(const std::string& word) const;
    [[nodiscard]] std::string getRandomWord() const;
    void emptyTable() const;

private:
    sqlite3* db{};
    std::string tableName;
};

#endif //WORDDAO_H
