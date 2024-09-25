#include "WordDao.h"
#include <stdexcept>

/**
 * @brief Constructor that opens a connection to the SQLite database and specifies the table.
 *
 * Initializes the DAO with the database path and table name where the words will be stored.
 *
 * @param dbPath Path to the SQLite database file.
 * @param tableName Name of the table in the database where words are stored.
 */
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

/**
 * @brief Destructor that closes the database connection.
 *
 * Ensures the SQLite database connection is properly closed when the object is destroyed.
 */
WordDAO::~WordDAO() {
    if (db != nullptr) {
        sqlite3_close(db);
    }
}

/**
 * @brief Adds a word to the specified table in the database.
 *
 * @param word The word to add to the database.
 */
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

/**
 * @brief Retrieves a random word from the table.
 *
 * Returns a randomly selected word from the database table.
 *
 * @return A random word from the table.
 */
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

/**
 * @brief Clears all words from the table.
 *
 * Empties the entire table by removing all stored words.
 */
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


