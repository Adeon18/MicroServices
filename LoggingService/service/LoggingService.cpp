#include "LoggingService.hpp"

namespace srv {
    LoggingServiceResource::LoggingServiceResource() {
        disallow_all();
        set_allowing("GET", true);
        set_allowing("POST", true);
    }

    std::shared_ptr<http_response> LoggingServiceResource::render_GET(const http_request& request) {
        spdlog::info(
                "Received GET from: " + std::string{request.get_requestor()} + ":" +
                std::to_string(request.get_requestor_port())
        );
        // Get all the messages from the map
        std::string response;
        for (auto& [uuid, msg]: m_storedData) {
            response += msg;
            response += ";";
        }

        spdlog::info("GET response: " + response);

        return std::shared_ptr<http_response>(new string_response(response));
    }

    std::shared_ptr<http_response> LoggingServiceResource::render_POST(const http_request& request) {
        spdlog::info(
                "Received GET from: " + std::string{request.get_requestor()} + ":" +
                std::to_string(request.get_requestor_port())
        );

        // Push the pair into the map
        const auto argsMap = request.get_args();
        for (auto& [key, msg]: argsMap) {
            std::string strKey = std::string{key};
            std::string strMsg = std::string{msg};

            spdlog::info("Received msg pair: [" + strKey + ", " + strMsg + "]");
            m_storedData[strKey] = strMsg;
        }

        return std::shared_ptr<http_response>(new string_response(POST_RESPONSE));
    }
} // srv