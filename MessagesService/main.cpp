#include <httpserver.hpp>

#include "Controller/MessageController.hpp"

namespace hs = httpserver;

int main(int argc, char** argv) {
    if (argc > 2) {
        std::cerr << "Too many arguments" << std::endl;
        return -1;
    }

    int port = 8084;
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

    bool blocking = false;
    hs::webserver facadeServer = hs::create_webserver(port);

    srv::MessageController fsr{};

    facadeServer.register_resource("/MessageService", &fsr);
    spdlog::info("Service at /MessageService started");
    facadeServer.start(blocking);

    while (true) {
        fsr.getMessageService().pollMQ();
    }

    return 0;
}
