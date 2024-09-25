#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <string>
#include "RatingDao.h"
#include "WordDao.h"
#include "CFG.h"

/**
 * @class Server
 * @brief The Server class provides the main interface for the application.
 *
 * It facilitates user interactions, allowing for sentence generation,
 * retrieval of top-rated sentences, and the population of word databases
 * from text files. The class utilizes the RatingDAO to manage sentence
 * ratings and incorporates multiple WordDAO instances for handling various
 * categories of words, including nouns, adjectives, verbs, prepositions,
 * and adverbs. It also employs the CFG class to generate sentences based
 * on context-free grammar. The server operates in a continuous loop,
 * prompting the user for actions until they decide to exit.
 */

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
