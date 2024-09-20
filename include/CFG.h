#ifndef CFG_H
#define CFG_H

#include <string>
#include <unordered_map>
#include <memory>
#include <random>
#include <vector>
#include "WordDao.h"

class CFG {
public:
    CFG(std::shared_ptr<WordDAO> nounDAO,
        std::shared_ptr<WordDAO> adjectiveDAO, std::shared_ptr<WordDAO> verbDAO,
        std::shared_ptr<WordDAO> prepositionDAO, std::shared_ptr<WordDAO> adverbDAO);
    ~CFG() = default;

    std::string generateSentence();

private:
    std::string generate(const std::string& state);

    std::unordered_map<std::string, std::shared_ptr<WordDAO>> terminals;
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> nonTerminals;

    std::default_random_engine generator{std::random_device{}()};
    std::uniform_int_distribution<size_t> dist;
};

#endif //CFG_H
