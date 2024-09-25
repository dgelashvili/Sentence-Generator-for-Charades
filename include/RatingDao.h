#ifndef RATINGDAO_H
#define RATINGDAO_H

#include <string>
#include <vector>
#include "sqlite3.h"


/**
 * @class RatingDAO
 * @brief Manages storing and retrieving sentence ratings from a SQLite database.
 *
 * RatingDAO allows users to add ratings to sentences and retrieve the top-rated sentences based on average ratings.
 * It interacts with the database to store new ratings and query the highest-rated sentences.
 */
class RatingDAO {
public:
    explicit RatingDAO(const std::string& dbPath);
    ~RatingDAO();

    void addRating(const std::string& sentence, int rating) const;
    [[nodiscard]] std::vector<std::pair<std::string, double>> getTopSentences(int num) const;

private:
    sqlite3* db{};
};

#endif //RATINGDAO_H
