#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <iostream>
#include <string>

inline std::string promptUser(const std::string& serverMessage) {
    std::string userInput;
    std::cout << serverMessage;
    std::cin >> userInput;
    return userInput;
}

inline int promptUserInt(const std::string& serverMessage, const int lower, const int higher) {
    int result;
    std::cout << serverMessage;
    while (!(std::cin >> result) || result < lower || result > higher) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input. " + serverMessage;
    }

    return result;
}

#endif //HELPERFUNCTIONS_H
