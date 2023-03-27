#include "Controller/LoggingController.hpp"

namespace hs = httpserver;

int main(int argc, char** argv) {
    if (argc > 2) {
        std::cerr << "Too many arguments" << std::endl;
        return -1;
    }

    int port = 8082;
    if (argc == 2) {
        try {
            port = std::stoi(argv[1]);
        }
        catch(std::invalid_argument const& ex)
        {
            std::cerr << "Invalid port number" << std::endl;
            return -1;
        }
    }

    bool blocking = true;
    hs::webserver facadeServer = hs::create_webserver(port);

    srv::LoggingController fsr{};

    facadeServer.register_resource("/LoggingService", &fsr);
    spdlog::info("Service at /LoggingService started");
    facadeServer.start(blocking);

    return 0;
}
