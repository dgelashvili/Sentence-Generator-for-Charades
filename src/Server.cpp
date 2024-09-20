#include <thread>
#include "Server.h"
#include "FileReader.h"
#include "HelperFunctions.h"

Server::Server(std::shared_ptr<RatingDAO> ratingDAO, std::shared_ptr<WordDAO> nounDAO,
            std::shared_ptr<WordDAO> adjectiveDAO, std::shared_ptr<WordDAO> verbDAO,
            std::shared_ptr<WordDAO> prepositionDAO, std::shared_ptr<WordDAO> adverbDAO)
    : ratingDAO(std::move(ratingDAO)), nounDAO(std::move(nounDAO)),
      adjectiveDAO(std::move(adjectiveDAO)), verbDAO(std::move(verbDAO)),
      prepositionDAO(std::move(prepositionDAO)), adverbDAO(std::move(adverbDAO)),
      cfg(this->nounDAO, this->adjectiveDAO, this->verbDAO, this->prepositionDAO, this->adverbDAO) {
}

void Server::start() {
    while (true) {
        std::string serverMessage = "What would you like to do?\n";
        serverMessage += "GenerateSentence(gen)/GetTopSentences(top)/FillWords(fill)/Exit(exit): ";

        if (std::string userInput = promptUser(serverMessage); userInput == "gen") {
            newSentence();
            system("cls");
        } else if (userInput == "top") {
            topSentences();
            system("cls");
        } else if (userInput == "fill") {
            fillWords();
            system("cls");
        } else if (userInput == "exit") {
            std::cout << "Goodbye!" << std::endl;
            break;
        } else {
            std::cout << "Unknown command: " + userInput << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            system("cls");
        }
    }
}

void Server::newSentence() {
    const std::string sentence = cfg.generateSentence();
    playWithSentence(sentence);
}

void Server::topSentences() const {
    system("cls");

    const std::vector<std::pair<std::string, double>> topSentences = ratingDAO->getTopSentences(5);
    std::cout << makeTable(topSentences) << std::endl;

    const std::string serverMessage = "\nType corresponding number to play with the sentence (type 0 to exit): ";
    const int choice = promptUserInt(serverMessage, 0, (int)topSentences.size());
    if (choice == 0) {
        std::cout << "Returning to main menu..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }
    const std::string sentence = topSentences[choice - 1].first;
    playWithSentence(sentence);
}

void Server::playWithSentence(const std::string& sentence) const {
    system("cls");
    const std::string serverMessage = "Your Sentence:  " + sentence;
    std::cout << serverMessage << std::endl;

    if (promptUser("Would you like to rate this sentence? (yes/no): ") == "yes") {
        const int rating = promptUserInt("Please enter the rating (1-5): ", 1, 5);
        ratingDAO->addRating(sentence, rating);
    }

    std::cout << "Returning to main menu..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void Server::fillWords() const {
    system("cls");
    std::cout << "If you want to use this command correctly, "
                    "please ensure that 'words' directory contains files:" << std::endl;
    std::cout << "Nouns.txt  Verbs.txt  Adjectives.txt Prepositions.txt Adverbs.txt" << std::endl;

    if (promptUser("Once you are ready, type 'ready': ") == "ready") {
        const auto nounReader = FileReader("../words/Nouns.txt", nounDAO);
        const auto verbReader = FileReader("../words/Verbs.txt", verbDAO);
        const auto adjectiveReader = FileReader("../words/Adjectives.txt", adjectiveDAO);
        const auto pronounReader = FileReader("../words/Prepositions.txt", prepositionDAO);
        const auto adverbReader = FileReader("../words/Adverbs.txt", adverbDAO);

        nounReader.readAndStore();
        verbReader.readAndStore();
        adjectiveReader.readAndStore();
        pronounReader.readAndStore();
        adverbReader.readAndStore();
    }

    std::cout << "Returning to main menu..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
}


