#include <httpserver.hpp>
#include <spdlog/spdlog.h>

#include "FacadeService.hpp"

FacadeService::FacadeService() {
    loggingServices.push_back(cpr::Url{"http://localhost:8082/LoggingService"});
    loggingServices.push_back(cpr::Url{"http://localhost:8083/LoggingService"});
    loggingServices.push_back(cpr::Url{"http://localhost:8084/LoggingService"});
}


void FacadeService::getMessages(std::vector<std::string> &messages) {
    getLoggingServiceData(messages);
    getMessageServiceData(messages);
}

std::string FacadeService::sendMessage(mod::Message &message) {
    message.uuid = util::generate_uuid_v4();

    spdlog::info("Service: Generated UUID pair: [" + message.uuid + ", " + message.text + "]");

    size_t loggingServiceIdx = rand() % loggingServices.size();

    spdlog::info("Service: Sending POST to: " + loggingServices[loggingServiceIdx].str());

    cpr::Response resp = cpr::Post(loggingServices[loggingServiceIdx], cpr::Payload{{message.uuid, message.text}});

    spdlog::info("Service: POST STATUS: " + std::to_string(resp.status_code));

    if (resp.status_code != 200) {
        return LOGGING_POST_FAIL;
    }

    return resp.text;
}

void FacadeService::getLoggingServiceData(std::vector<std::string>& msgs) {
    size_t loggingServiceIdx = rand() % loggingServices.size();
    // Send GET to LoggingService
    spdlog::info("Service: Sending GET to: " + loggingServices[loggingServiceIdx].str());
    cpr::Response respLogging = cpr::Get(loggingServices[loggingServiceIdx]);
    spdlog::info("Service: GET STATUS: " + std::to_string(respLogging.status_code));

    std::string loggingMessage = respLogging.text;
    if (respLogging.status_code != 200) {
        loggingMessage = LOGGING_GET_FAIL;
    }

    msgs.push_back(loggingMessage);
}

void FacadeService::getMessageServiceData(std::vector<std::string> &msgs) {
    // Send GET to MessagesService
    spdlog::info("Service: Sending GET to: " + MESSAGES_SERVICE_ADDRESS);
    cpr::Response respMessages = cpr::Get(cpr::Url{MESSAGES_SERVICE_ADDRESS});
    spdlog::info("Service: GET STATUS: " + std::to_string(respMessages.status_code));

    msgs.push_back(respMessages.text);
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