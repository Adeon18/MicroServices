#include <httpserver.hpp>

#include "Controller/MessageController.hpp"

namespace hs = httpserver;

int main(int argc, char** argv) {
    bool blocking = false;
    hs::webserver facadeServer = hs::create_webserver(8084);

    srv::MessageController fsr{};

    facadeServer.register_resource("/MessageService", &fsr);
    spdlog::info("Service at /MessageService started");
    facadeServer.start(blocking);

    while (true) {
        fsr.getMessageService().pollMQ();
    }

    return 0;
}
