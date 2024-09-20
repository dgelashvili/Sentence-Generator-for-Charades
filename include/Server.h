#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <string>
#include "RatingDao.h"
#include "WordDao.h"
#include "CFG.h"

class Server {
public:
    Server(std::shared_ptr<RatingDAO> ratingDAO, std::shared_ptr<WordDAO> nounDAO,
        std::shared_ptr<WordDAO> adjectiveDAO, std::shared_ptr<WordDAO> verbDAO,
        std::shared_ptr<WordDAO> prepositionDAO, std::shared_ptr<WordDAO> adverbDAO);
    ~Server() = default;

    void start();
private:
    void newSentence();
    void topSentences() const;
    void playWithSentence(const std::string& sentence) const;
    void fillWords() const;

    std::shared_ptr<RatingDAO> ratingDAO;
    std::shared_ptr<WordDAO> nounDAO;
    std::shared_ptr<WordDAO> adjectiveDAO;
    std::shared_ptr<WordDAO> verbDAO;
    std::shared_ptr<WordDAO> prepositionDAO;
    std::shared_ptr<WordDAO> adverbDAO;

    CFG cfg;
};

#endif //SERVER_H
