#include "Server.h"
#include "HelperFunctions.h"
#include <thread>

Server::Server(std::shared_ptr<RatingDAO> ratingDAO)
    : ratingDAO(std::move(ratingDAO)) {}

void Server::start() {
    while (true) {
        std::string serverMessage = "What would you like to do?\n";
        serverMessage += "(GenerateSentence/GetTopSentences/FillWords/Exit): ";

        if (std::string userInput = promptUser(serverMessage); userInput == "GenerateSentence") {
            newSentence();
            system("cls");
        } else if (userInput == "GetTopSentences") {
            topSentences();
            system("cls");
        } else if (userInput == "FillWords") {
            fillWords();
            system("cls");
        } else if (userInput == "Exit") {
            std::cout << "Goodbye!" << std::endl;
            break;
        } else {
            std::cout << "Unknown command: " + userInput << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            system("cls");
        }
    }
}

void Server::newSentence() const {
    const std::string sentence = "taxi taxi taxi"; //= generate new sentence
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

void Server::fillWords() {
    system("cls");
    std::cout << "If you want to use this command correctly, "
                    "please ensure that 'words' directory contains files:" << std::endl;
    std::cout << "Nouns.pdf    Verbs.pdf     Adjectives.pdf" << std::endl;

    if (promptUser("Once you are ready, type 'ready': ") == "ready") {
        // add words to db
    }

    std::cout << "Returning to main menu..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}


