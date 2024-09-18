#ifndef RATINGDAO_H
#define RATINGDAO_H

#include <string>
#include <vector>
#include "sqlite3.h"

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
