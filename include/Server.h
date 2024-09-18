#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <string>
#include "RatingDao.h"

class Server {
public:
    Server(std::shared_ptr<RatingDAO> ratingDAO);
    ~Server() = default;

    void start();
private:
    void newSentence() const;
    void topSentences() const;
    void playWithSentence(const std::string& sentence) const;
    void fillWords();

    std::shared_ptr<RatingDAO> ratingDAO;
};

#endif //SERVER_H
