#include "CFG.h"
#include <utility>

CFG::CFG(std::shared_ptr<WordDAO> nounDAO, std::shared_ptr<WordDAO> adjectiveDAO,
    std::shared_ptr<WordDAO> verbDAO, std::shared_ptr<WordDAO> prepositionDAO,
    std::shared_ptr<WordDAO> adverbDAO) {
    terminals["N"] = std::move(nounDAO);
    terminals["Adj"] = std::move(adjectiveDAO);
    terminals["V"] = std::move(verbDAO);
    terminals["P"] = std::move(prepositionDAO);
    terminals["Adv"] = std::move(adverbDAO);

    nonTerminals["sentence"] = {{"NPhrase", "VPhrase"}};
    nonTerminals["NPhrase"] = {{"the", "N"}, {"the", "AdjPhrase", "N"},
        {"the", "N", "PPhrase"}};
    nonTerminals["VPhrase"] = {{"V"}, {"V", "NPhrase"}, {"V", "NPhrase", "PPhrase"},
        {"V", "AdvPhrase"}, {"V", "NPhrase", "AdvPhrase"},
        {"V", "NPhrase", "PPhrase", "AdvPhrase"}};
    nonTerminals["AdjPhrase"] = {{"Adj"}, {"Adj", "AdjPhrase"}};
    nonTerminals["PPhrase"] = {{"P", "NPhrase"}};
    nonTerminals["AdvPhrase"] = {{"Adv"}, {"Adv", "AdvPhrase"}};
}

std::string CFG::generateSentence() {
    return generate("sentence");
}

std::string CFG::generate(const std::string& state) {
    if (state == "the") return state + " ";
    if (terminals.contains(state)) return terminals[state]->getRandomWord() + " ";

    dist = std::uniform_int_distribution<size_t>(0, nonTerminals[state].size() - 1);
    const int index = (int)dist(generator);

    std::string result;
    for (const auto& newState : nonTerminals[state][index]) {
        result += generate(newState);
    }

    return result;
}
