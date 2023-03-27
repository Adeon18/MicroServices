#include <httpserver.hpp>
#include <spdlog/spdlog.h>

#include "FacadeService.hpp"

void FacadeService::getMessages(std::vector<std::string> &messages) {
    // Send GET to LoggingService
    spdlog::info("Service: Sending GET to: " + LOGGING_SERVICE_ADDRESS);
    cpr::Response respLogging = cpr::Get(cpr::Url{LOGGING_SERVICE_ADDRESS});
    spdlog::info("Service: GET STATUS: " + std::to_string(respLogging.status_code));
    // Send GET to MessagesService
    spdlog::info("Service: Sending GET to: " + MESSAGES_SERVICE_ADDRESS);
    cpr::Response respMessages = cpr::Get(cpr::Url{MESSAGES_SERVICE_ADDRESS});
    spdlog::info("Service: GET STATUS: " + std::to_string(respLogging.status_code));

    messages.push_back(respLogging.text);
    messages.push_back(respMessages.text);
}

cpr::Response FacadeService::sendMessage(mod::Message &message) {
    message.uuid = util::generate_uuid_v4();

    spdlog::info("Service: Generated UUID pair: [" + message.uuid + ", " + message.text + "]");

    spdlog::info("Service: Sending POST to: " + LOGGING_SERVICE_ADDRESS);

    cpr::Response resp = cpr::Post(cpr::Url{LOGGING_SERVICE_ADDRESS}, cpr::Payload{{message.uuid, message.text}});

    spdlog::info("Service: POST STATUS: " + std::to_string(resp.status_code));

    return resp;
}

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