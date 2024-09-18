#include "Server.h"

int main() {
    std::string dbPath = "../database.sqlite";

    const auto ratingDAO = std::make_shared<RatingDAO>(dbPath);

    auto server = Server(ratingDAO);
    server.start();
    return 0;
}
