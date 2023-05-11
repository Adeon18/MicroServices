#include "Controller/FacadeController.hpp"

namespace hs = httpserver;

int main(int argc, char** argv) {
    if (argc > 2) {
        std::cerr << "Too many arguments" << std::endl;
        return -1;
    }

    int port = 8080;
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

    //std::cout << kv.get("MQNAME", "default-value") << std::endl;

    bool blocking = true;
    hs::webserver facadeServer = hs::create_webserver(port);

    srv::FacadeController fsr{port};

    facadeServer.register_resource("/FacadeService", &fsr);
    spdlog::info("Service at /FacadeService started");
    facadeServer.start(blocking);

    return 0;
}