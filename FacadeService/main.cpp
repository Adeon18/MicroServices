#include "Controller/FacadeController.hpp"

#include "ppconsul/agent.h"

using ppconsul::Consul;
using namespace ppconsul::agent;

namespace hs = httpserver;

int main(int argc, char** argv) {

    // Create a consul client that uses default local endpoint `http://127.0.0.1:8500` and default data center
    Consul consul;
// We need the 'agent' endpoint for a service registration
    Agent agent(consul);

// Register a service with associated HTTP check:
    agent.registerService(
            kw::name = "my-service",
            kw::port = 9876,
            kw::tags = {"tcp", "super_server"},
            kw::check = HttpCheck{"http://localhost:80/", std::chrono::seconds(2)}
    );

    bool blocking = true;
    hs::webserver facadeServer = hs::create_webserver(8080);

    srv::FacadeController fsr{};

    facadeServer.register_resource("/FacadeService", &fsr);
    spdlog::info("Service at /FacadeService started");
    facadeServer.start(blocking);

    return 0;
}