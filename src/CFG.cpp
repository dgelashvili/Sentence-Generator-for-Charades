#include "CFG.h"
#include <utility>

/**
 * @brief Constructs the CFG object with DAO objects for different word types.
 *
 * The constructor initializes terminal symbols (e.g., nouns, adjectives, etc.) with their corresponding
 * DAO objects, and sets up the non-terminal grammar rules that represent sentence structure.
 *
 * @param nounDAO Shared pointer to the WordDAO for nouns.
 * @param adjectiveDAO Shared pointer to the WordDAO for adjectives.
 * @param verbDAO Shared pointer to the WordDAO for verbs.
 * @param prepositionDAO Shared pointer to the WordDAO for prepositions.
 * @param adverbDAO Shared pointer to the WordDAO for adverbs.
 */
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
    nonTerminals["PPhrase"] = {{"P", "the", "N"}, {"P", "the", "AdjPhrase", "N"}};
    nonTerminals["AdvPhrase"] = {{"Adv"}, {"Adv", "AdvPhrase"}};
}

/**
 * @brief Generates a random sentence by initiating the recursive generation process.
 *
 * This method starts the sentence generation process by calling the recursive 'generate'
 * method on the "sentence" non-terminal, which leads to constructing the full sentence.
 *
 * @return A string containing the generated sentence.
 */
std::string CFG::generateSentence() {
    return generate("sentence");
}

/**
 * @brief Recursively generates parts of the sentence by expanding grammar rules.
 *
 * This method takes a grammatical state (either terminal or non-terminal) and recursively
 * generates the corresponding part of the sentence. If it's a terminal, it fetches a word
 * from the DAO, and if it's a non-terminal, it applies the rules to generate further.
 *
 * @param state The current state (non-terminal or terminal symbol) being expanded.
 * @return A string representing the generated part of the sentence.
 */
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
