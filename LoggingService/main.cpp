#include "Controller/LoggingController.hpp"

namespace hs = httpserver;

int main() {
    bool blocking = true;
    hs::webserver facadeServer = hs::create_webserver(8081);

    srv::LoggingController fsr{};

    facadeServer.register_resource("/LoggingService", &fsr);
    spdlog::info("Service at /LoggingService started");
    facadeServer.start(blocking);

    return 0;
}
