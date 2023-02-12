#ifndef MICROSERVICES_FACADESERVICE_HPP
#define MICROSERVICES_FACADESERVICE_HPP

#include <iostream>
#include <random>
#include <sstream>

#include <unordered_map>

#include <httpserver.hpp>

namespace srv {
    using namespace httpserver;
    static constexpr int SERVICE_PORT = 8081;

    template<int port>
    class LoggingService {
    public:
        void registerService(http_resource *hptr) {
            m_webServer.register_resource("/LoggingService", hptr);
        }

        void start() { m_webServer.start(true); }
    private:
        webserver m_webServer = create_webserver(port);
    };

    class LoggingServiceResource : public http_resource {
        inline static std::string GET_RESPONSE = "Logging server GET response placeholder";
        inline static std::string POST_RESPONSE = "Logging successful";
    public:
        LoggingServiceResource() {
            disallow_all();
            set_allowing("GET", true);
            set_allowing("POST", true);
        }
        std::shared_ptr<http_response> render_GET(const http_request&) override {

            std::string response;
            for (auto& [uuid, msg]: m_storedData) {
                response += msg;
                response += ";";
            }

            return std::shared_ptr<http_response>(new string_response(response));
        }

        std::shared_ptr<http_response> render_POST(const http_request& request) override {
            const auto argsMap = request.get_args();
            for (auto& [key, arg]: argsMap) {
                std::cout << "Key: " << key << " Arg: " << arg << std::endl;
                m_storedData[std::string{key.begin(), key.end()}] = std::string{arg.begin(), arg.end()};
            }

            return std::shared_ptr<http_response>(new string_response(POST_RESPONSE));
        }

    private:
        std::unordered_map<std::string, std::string> m_storedData;
    };
} // srv

#endif //MICROSERVICES_FACADESERVICE_HPP
