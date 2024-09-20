#include "RatingDao.h"
#include <stdexcept>

RatingDAO::RatingDAO(const std::string& dbPath)
    : db(nullptr)
{
    if (sqlite3_open(dbPath.c_str(), &db)) {
        throw std::runtime_error("Could not open database");
    }
    const std::string createTableSQL = "CREATE TABLE IF NOT EXISTS Ratings ("
                                        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                        "Sentence TEXT NOT NULL, "
                                        "Rating DOUBLE NOT NULL"
                                        ");";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, createTableSQL.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::string error = "Ratings: ";
        error += errMsg;
        sqlite3_free(errMsg);
        throw std::runtime_error(error);
    }
}

RatingDAO::~RatingDAO() {
    if (db != nullptr) {
        sqlite3_close(db);
    }
}

void RatingDAO::addRating(const std::string& sentence, const int rating) const {
    sqlite3_stmt* stmt;
    const std::string insertSQL = "INSERT INTO Ratings (Sentence, Rating) VALUES (?, ?);";
    if (sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare statement");
    }
    sqlite3_bind_text(stmt, 1, sentence.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, std::to_string((double)rating).c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::string error = "Failed to add rating: ";
        error += sqlite3_errmsg(db);
        throw std::runtime_error(error);
    }

    sqlite3_finalize(stmt);
}

std::vector<std::pair<std::string, double>> RatingDAO::getTopSentences(int num) const {
    sqlite3_stmt* stmt;
    const std::string sql = "SELECT sentence, AVG(Rating) AS avg_rating "
                            "FROM Ratings "
                            "GROUP BY sentence "
                            "ORDER BY avg_rating DESC;";
    std::vector<std::pair<std::string, double>> topSentences;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare statement");
    }

    while (sqlite3_step(stmt) == SQLITE_ROW && num--) {
        auto sentence = (const char*)(sqlite3_column_text(stmt, 0));
        double avg_rating = sqlite3_column_double(stmt, 1);
        topSentences.emplace_back(sentence, avg_rating);
    }

    sqlite3_finalize(stmt);
    return topSentences;
}