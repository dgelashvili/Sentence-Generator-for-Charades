#include "WordDao.h"
#include <stdexcept>

WordDAO::WordDAO(const std::string &dbPath, const std::string& tableName)
    : db(nullptr), tableName(tableName)
{
    if (sqlite3_open(dbPath.c_str(), &db)) {
        throw std::runtime_error("Could not open database");
    }
    const std::string createTableSQL = "CREATE TABLE IF NOT EXISTS " + tableName + " ("
                                        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                        "Word TEXT NOT NULL"
                                        ");";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, createTableSQL.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::string error = tableName + ": ";
        error += errMsg;
        sqlite3_free(errMsg);
        throw std::runtime_error(error);
    }
}

WordDAO::~WordDAO() {
    if (db != nullptr) {
        sqlite3_close(db);
    }
}

void WordDAO::addWord(const std::string &word) const {
    sqlite3_stmt* stmt;
    const std::string insertSQL = "INSERT INTO " + tableName + " (Word) VALUES (?);";
    if (sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare statement");
    }
    sqlite3_bind_text(stmt, 1, word.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::string error = "Failed to add word: ";
        error += sqlite3_errmsg(db);
        throw std::runtime_error(error);
    }

    sqlite3_finalize(stmt);
}

std::string WordDAO::getRandomWord() const {
    sqlite3_stmt* stmt;
    const std::string sql = "SELECT word "
                            "FROM " + tableName + " "
                            "ORDER BY RANDOM() "
                            "LIMIT 1;";
    std::string word;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare statement");
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        word = (const char*)(sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);
    return word;
}

void WordDAO::emptyTable() const {
    const std::string sql = "DELETE FROM " + tableName + ";";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::string error = tableName + ": ";
        error += errMsg;
        sqlite3_free(errMsg);
        throw std::runtime_error(error);
    }
}


