#ifndef MICROSERVICES_LOGGINGSERVICE_HPP
#define MICROSERVICES_LOGGINGSERVICE_HPP

#include <iostream>
#include <random>
#include <sstream>

#include <unordered_map>

#include <spdlog/spdlog.h>
#include <httpserver.hpp>

namespace srv {
    using namespace httpserver;
    static constexpr int SERVICE_PORT = 8081;

    //! Logging server wrapper
    template<int port>
    class LoggingService {
        inline static std::string PATH = "/LoggingService";
    public:
        void registerService(http_resource *hptr) {
            m_webServer.register_resource(PATH, hptr);
        }

        void start() {
            spdlog::info("Server at " + PATH + " started");
            m_webServer.start(true);
        }
    private:
        webserver m_webServer = create_webserver(port);
    };

    //! Logging service
    class LoggingServiceResource : public http_resource {
        inline static std::string POST_RESPONSE = "Message Logged";
    public:
        LoggingServiceResource();
        //! Logging GET response
        std::shared_ptr<http_response> render_GET(const http_request& request) override;
        //! Logging POST operations
        std::shared_ptr<http_response> render_POST(const http_request& request) override;

    private:
        std::unordered_map<std::string, std::string> m_storedData;
    };
} // srv

#endif //MICROSERVICES_LOGGINGSERVICE_HPP
