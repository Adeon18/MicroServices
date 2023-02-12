#ifndef MICROSERVICES_FACADESERVICE_HPP
#define MICROSERVICES_FACADESERVICE_HPP

#include <random>
#include <sstream>

#include <httpserver.hpp>
#include <spdlog/spdlog.h>

namespace util {
    std::string generate_uuid_v4();
} // util

namespace srv {
    using namespace httpserver;
    static constexpr int SERVICE_PORT = 8080;

    //! Facader service class
    template<int port>
    class FacadeService {
        inline static std::string PATH = "/FacadeService";
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

    //! Facade Service Resourse
    class FacadeServiceResource : public http_resource {
        inline static std::string GET_RESPONSE = "Facade server GET response placeholder";
        inline static std::string POST_RESPONSE = "Facade server POST response placeholder";
        inline static std::string MESSAGES_SERVICE_ADDRESS = "http://localhost:8082/MessageService";
        inline static std::string LOGGING_SERVICE_ADDRESS = "http://localhost:8081/LoggingService";
    public:
        FacadeServiceResource();

        //! Send get requests to MessageService and Logging Service and return respective data
        std::shared_ptr<http_response> render_GET(const http_request &request) override;
        //! Generate UUID and send a post request to Logging Service
        std::shared_ptr<http_response> render_POST(const http_request &request) override;
    };
} // srv

#endif //MICROSERVICES_FACADESERVICE_HPP
