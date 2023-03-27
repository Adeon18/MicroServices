#include "Controller/FacadeController.hpp"

namespace hs = httpserver;

int main(int argc, char** argv) {

    bool blocking = true;
    hs::webserver facadeServer = hs::create_webserver(8080);

    srv::FacadeController fsr{};

    facadeServer.register_resource("/FacadeService", &fsr);
    spdlog::info("Service at /FacadeService started");
    facadeServer.start(blocking);

    return 0;
}