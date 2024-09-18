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

inline std::string border = "--------------------------------------------------------------\n";

inline std::string makeRow(const std::pair<std::string, double>& info) {
    std::string sentence = info.first;
    if (sentence.size() > 43) {
        sentence = sentence.substr(0, 43);
    } else {
        int size = 43 - (int)sentence.size();
        while (size--) {
            sentence += " ";
        }
    }
    std::string rating = std::to_string(info.second);
    if (rating.size() > 6) {
        rating = rating.substr(0, 6);
    } else {
        int size = 6 - (int)rating.size();
        while (size--) {
            rating += " ";
        }
    }
    return  "| " + sentence + " |  " + rating + "  |\n";
}

inline std::string makeTable(const std::vector<std::pair<std::string, double>>& info) {
    std::string result;
    result += border;
    result += "| # |                 Sentence                    |  Rating  |\n";
    result += border;

    int index = 0;
    for (const auto & singleInfo : info) {
        index++;
        result += "| " + std::to_string(index) + " " + makeRow(singleInfo);
    }
    result += border;
    return result;
}

#endif //HELPERFUNCTIONS_H