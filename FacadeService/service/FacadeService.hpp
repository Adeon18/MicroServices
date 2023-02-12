#ifndef MICROSERVICES_FACADESERVICE_HPP
#define MICROSERVICES_FACADESERVICE_HPP

#include <random>
#include <sstream>

#include <httpserver.hpp>

namespace util {
    // UUID generation taken from
    // https://stackoverflow.com/questions/24365331/how-can-i-generate-uuid-in-c-without-using-boost-library
    static std::random_device              rd;
    static std::mt19937                    gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);

    std::string generate_uuid_v4() {
        std::stringstream ss;
        int i;
        ss << std::hex;
        for (i = 0; i < 8; i++) {
            ss << dis(gen);
        }
        ss << "-";
        for (i = 0; i < 4; i++) {
            ss << dis(gen);
        }
        ss << "-4";
        for (i = 0; i < 3; i++) {
            ss << dis(gen);
        }
        ss << "-";
        ss << dis2(gen);
        for (i = 0; i < 3; i++) {
            ss << dis(gen);
        }
        ss << "-";
        for (i = 0; i < 12; i++) {
            ss << dis(gen);
        };
        return ss.str();
    }
} // util

namespace srv {
    using namespace httpserver;
    static constexpr int SERVICE_PORT = 8080;

    template<int port>
    class FacadeService {
    public:
        void registerService(http_resource *hptr) {
            m_webServer.register_resource("/FacadeService", hptr);
        }

        void start() { m_webServer.start(true); }
    private:
        webserver m_webServer = create_webserver(port);
    };

    class FacadeServiceResource : public http_resource {
        inline static std::string GET_RESPONSE = "Facade server GET response placeholder";
        inline static std::string POST_RESPONSE = "Facade server POST response placeholder";
    public:
        FacadeServiceResource() {
            disallow_all();
            set_allowing("GET", true);
            set_allowing("POST", true);
        }
        std::shared_ptr<http_response> render_GET(const http_request&) override {
            cpr::Response respLogging = cpr::Get(cpr::Url{"http://localhost:8081/LoggingService"});
            cpr::Response respMessages = cpr::Get(cpr::Url{"http://localhost:8082/MessagesService"});

            std::string response;
            response += "LoggingService: " + respLogging.text + " | ";
            response += "MessagesService: " + respMessages.text;

            return std::shared_ptr<http_response>(new string_response(response));
        }

        std::shared_ptr<http_response> render_POST(const http_request& request) override {
            std::string uuid = util::generate_uuid_v4();
            auto msgStrView = request.get_content();
            std::string message = {msgStrView.begin(), msgStrView.end()};

            std::cout << "UUID Generated: " << uuid << std::endl;
            std::cout << "Request message: " << message << std::endl;

            cpr::Response r = cpr::Post(cpr::Url{"http://localhost:8081/LoggingService"},
                                        cpr::Payload{{uuid, message}});

            return std::shared_ptr<http_response>(new string_response(r.text));
        }
    };
} // srv

#endif //MICROSERVICES_FACADESERVICE_HPP
