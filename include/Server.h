#ifndef SERVER_H
#define SERVER_H

#include <string>

class Server {
public:
    Server();
    ~Server() = default;

    void start();
private:
    void newSentence();
    void topSentences();
    void playWithSentence(const std::string& sentence);
    void fillWords();
};

#endif //SERVER_H
