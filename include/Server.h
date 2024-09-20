#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <string>
#include "RatingDao.h"
#include "WordDao.h"

class Server {
public:
    Server(std::shared_ptr<RatingDAO> ratingDAO, std::shared_ptr<WordDAO> nounDAO,
        std::shared_ptr<WordDAO> adjectiveDAO, std::shared_ptr<WordDAO> verbDAO,
        std::shared_ptr<WordDAO> pronounDAO, std::shared_ptr<WordDAO> adverbDAO);
    ~Server() = default;

    void start();
private:
    void newSentence() const;
    void topSentences() const;
    void playWithSentence(const std::string& sentence) const;
    void fillWords() const;

    std::shared_ptr<RatingDAO> ratingDAO;
    std::shared_ptr<WordDAO> nounDAO;
    std::shared_ptr<WordDAO> adjectiveDAO;
    std::shared_ptr<WordDAO> verbDAO;
    std::shared_ptr<WordDAO> pronounDAO;
    std::shared_ptr<WordDAO> adverbDAO;
};

#endif //SERVER_H
