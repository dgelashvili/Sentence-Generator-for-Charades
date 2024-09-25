#ifndef WORDDAO_H
#define WORDDAO_H

#include <string>
#include "sqlite3.h"

/**
 * @class WordDAO
 * @brief Manages word storage and retrieval for a specific table in an SQLite database.
 *
 * WordDAO provides methods to add words to a table, retrieve random words, and clear the table.
 * Each instance operates on a specific table within the database.
 */
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
