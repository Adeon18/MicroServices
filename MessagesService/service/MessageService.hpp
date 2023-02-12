#ifndef MICROSERVICES_MESSAGESERVICE_HPP
#define MICROSERVICES_MESSAGESERVICE_HPP

#include <iostream>
#include <random>
#include <sstream>

#include <unordered_map>

#include <spdlog/spdlog.h>
#include <httpserver.hpp>

namespace srv {
    using namespace httpserver;
    static constexpr int SERVICE_PORT = 8082;

    //! Logging server wrapper
    template<int port>
    class MessageService {
        inline static std::string PATH = "/MessageService";
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
    class MessageServiceResource : public http_resource {
        inline static std::string GET_RESPONSE = "Message server GET response placeholder";
    public:
        MessageServiceResource() {
            disallow_all();
            set_allowing("GET", true);
        }
        std::shared_ptr<http_response> render_GET(const http_request& request) override {
            spdlog::info(
                    "Received GET from: " + std::string{request.get_requestor()} + ":" +
                        std::to_string(request.get_requestor_port())
            );
            return std::shared_ptr<http_response>(new string_response(GET_RESPONSE));
        }
    };
} // srv

#endif //MICROSERVICES_MESSAGESERVICE_HPP
