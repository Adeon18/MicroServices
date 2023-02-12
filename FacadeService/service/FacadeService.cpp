#include <iostream>

#include <cpr/cpr.h>

#include "FacadeService.hpp"

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
    FacadeServiceResource::FacadeServiceResource() {
        disallow_all();
        set_allowing("GET", true);
        set_allowing("POST", true);
    }
    std::shared_ptr<http_response> FacadeServiceResource::render_GET(const http_request& request) {
        spdlog::info("Received GET from: " + std::string{request.get_requestor()} + ":" + std::to_string(request.get_requestor_port()));

        // Send GET to LoggingService
        spdlog::info("Sending GET to: " + LOGGING_SERVICE_ADDRESS);
        cpr::Response respLogging = cpr::Get(cpr::Url{LOGGING_SERVICE_ADDRESS});
        spdlog::info("GET STATUS: " + std::to_string(respLogging.status_code));
        // Send GET to MessagesService
        spdlog::info("Sending GET to: " + MESSAGES_SERVICE_ADDRESS);
        cpr::Response respMessages = cpr::Get(cpr::Url{MESSAGES_SERVICE_ADDRESS});
        spdlog::info("GET STATUS: " + std::to_string(respLogging.status_code));

        std::string response;
        response += respLogging.text + " | " + respMessages.text;

        return std::shared_ptr<http_response>(new string_response(response));
    }

    std::shared_ptr<http_response> FacadeServiceResource::render_POST(const http_request& request) {
        spdlog::info("Received POST from: " + std::string{request.get_requestor()} + ":" + std::to_string(request.get_requestor_port()));

        std::string uuid = util::generate_uuid_v4();
        std::string message = std::string{request.get_content()};

        spdlog::info("Generated UUID pair: [" + uuid + ", " + message + "]");

        spdlog::info("Sending POST to: " + LOGGING_SERVICE_ADDRESS);
        cpr::Response respLogging = cpr::Post(cpr::Url{LOGGING_SERVICE_ADDRESS},
                                    cpr::Payload{{uuid, message}});
        spdlog::info("POST STATUS: " + std::to_string(respLogging.status_code));

        return std::shared_ptr<http_response>(new string_response(respLogging.text));
    }
} // srv