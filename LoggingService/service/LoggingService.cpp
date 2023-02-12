#include "LoggingService.hpp"

namespace srv {
    LoggingServiceResource::LoggingServiceResource() {
        disallow_all();
        set_allowing("GET", true);
        set_allowing("POST", true);
    }

    std::shared_ptr<http_response> LoggingServiceResource::render_GET(const http_request&) {

        std::string response;
        for (auto& [uuid, msg]: m_storedData) {
            response += msg;
            response += ";";
    }

    return std::shared_ptr<http_response>(new string_response(response));
    }

    std::shared_ptr<http_response> LoggingServiceResource::render_POST(const http_request& request) {
        const auto argsMap = request.get_args();
        for (auto& [key, arg]: argsMap) {
            std::cout << "Key: " << key << " Arg: " << arg << std::endl;
            m_storedData[std::string{key.begin(), key.end()}] = std::string{arg.begin(), arg.end()};
        }

        return std::shared_ptr<http_response>(new string_response(POST_RESPONSE));
    }
} // srv