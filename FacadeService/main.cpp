#include "Controller/FacadeController.hpp"

#include "ppconsul/agent.h"
#include "ppconsul/kv.h"

using ppconsul::Consul;
using namespace ppconsul::agent;


namespace hs = httpserver;

int main(int argc, char** argv) {

    // Create a consul client that uses default local endpoint `http://127.0.0.1:8500` and default data center
    Consul consul;
// We need the 'agent' endpoint for a service registration
    Agent agent(consul);;

    ppconsul::kv::Kv kv(consul);
// Register a service with associated HTTP check:
    agent.registerService("FacadeService",
            kw::name = "FacadeService",
            kw::address = "127.0.0.1",
            kw::port = 8080,
            kw::id = "FacadeService1",
            kw::check = HttpCheck{"http://127.0.0.1:8080/FacadeService", std::chrono::seconds(2)}
    );
    agent.registerService("FacadeService",
            kw::name = "FacadeService",
            kw::address = "127.0.0.1",
            kw::port = 8081,
            kw::id = "FacadeService2",
            kw::check = HttpCheck{"http://localhost:81/FacadeService", std::chrono::seconds(2)}
    );

    std::cout << consul.get("/v1/agent/services") << std::endl;

    std::cout << kv.get("MQNAME", "default-value") << std::endl;

    bool blocking = true;
    hs::webserver facadeServer = hs::create_webserver(8080);

    srv::FacadeController fsr{};

    facadeServer.register_resource("/FacadeService", &fsr);
    spdlog::info("Service at /FacadeService started");
    facadeServer.start(blocking);

    return 0;
}