#define CROW_USE_ASIO
#include "server/Server.h"
#include <iostream>

int main() {
    try {
        Server server(18080);
        server.run();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
