#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <iostream>
#include <string>

/**
 * @brief Prompts the user for a string input with a message from the server.
 *
 * Displays a message to the user and captures a single word input.
 *
 * @param serverMessage Message to display to the user.
 * @return The user's input as a string.
 */
inline std::string promptUser(const std::string& serverMessage) {
    std::string userInput;
    std::cout << serverMessage;
    std::cin >> userInput;
    return userInput;
}

/**
 * @brief Prompts the user for an integer input within a specified range.
 *
 * Repeatedly asks the user for input until a valid integer between the lower and higher bounds is provided.
 *
 * @param serverMessage Message to display to the user.
 * @param lower Minimum valid integer.
 * @param higher Maximum valid integer.
 * @return The user's input as an integer within the range.
 */
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

/**
 * @brief Formats a single row of sentence and rating for display in a table.
 *
 * Adjusts sentence and rating to fit within column widths and returns a formatted table row.
 *
 * @param info A pair containing a sentence and its associated rating.
 * @return A formatted string representing a row in the table.
 */
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

/**
 * @brief Constructs a formatted table displaying sentences and ratings.
 *
 * Builds a table with numbered rows showing each sentence and its rating, formatted for display.
 *
 * @param info A vector of pairs, where each pair consists of a sentence and its rating.
 * @return A formatted string representing the complete table.
 */
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