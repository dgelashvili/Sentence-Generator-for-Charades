#include "Server.h"

int main() {
    std::string dbPath = "../database.sqlite";

    const auto ratingDAO = std::make_shared<RatingDAO>(dbPath);
    const auto nounDAO = std::make_shared<WordDAO>(dbPath, "Nouns");
    const auto adjectiveDAO = std::make_shared<WordDAO>(dbPath, "Adjectives");
    const auto verbDAO = std::make_shared<WordDAO>(dbPath, "Verbs");
    const auto pronounDAO = std::make_shared<WordDAO>(dbPath, "Pronouns");
    const auto adverbDAO = std::make_shared<WordDAO>(dbPath, "Adverbs");

    auto server = Server(ratingDAO, nounDAO, adjectiveDAO, verbDAO, pronounDAO, adverbDAO);
    server.start();
    return 0;
}
