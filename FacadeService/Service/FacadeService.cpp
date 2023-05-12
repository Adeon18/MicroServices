#include <httpserver.hpp>
#include <spdlog/spdlog.h>
#include <ppconsul/kv.h>

#include "json.hpp"

#include "FacadeService.hpp"

using json = nlohmann::json;

FacadeService::FacadeService(int port): hzClient{hazelcast::new_client().get()}, consul{}, consulAgent(consul), consulKV{consul} {
    consulAgent.registerService(
            "FacadeService",
            ppconsul::agent::kw::name = "FacadeService",
            ppconsul::agent::kw::address = "127.0.0.1",
            ppconsul::agent::kw::port = port,
            ppconsul::agent::kw::id = "FacadeService" + std::to_string(port)
    );
    std::string mqName = consulKV.get("MQNAME", "DEF");
    if (mqName == "DEF") { spdlog::info("Service: Could not get the MQ by name" ); }
    messageQueue = hzClient.get_queue(mqName).get();
}


void FacadeService::getMessages(std::vector<std::string> &messages) {
    getLoggingServiceData(messages);
    getMessageServiceData(messages);
}

std::optional<std::string> FacadeService::sendMessageToLogging(mod::MessageUUID &message) {
    message.uuid = util::generate_uuid_v4();

    spdlog::info("Service: Generated UUID pair: [" + message.uuid + ", " + message.text + "]");

    auto serviceChosen = getServiceFromConsul(LOGGING_SERVICE_CONSUL_GET);
    if (!serviceChosen) {
        spdlog::info("Service: No Logging services available");
        return {};
    }

    spdlog::info("Service: Sending POST to: " + serviceChosen->str());

    cpr::Response resp = cpr::Post(*serviceChosen, cpr::Payload{{message.uuid, message.text}});

    spdlog::info("Service: POST STATUS: " + std::to_string(resp.status_code));

    if (resp.status_code != 200) {
        return {};
    }

    return resp.text;
}

void FacadeService::pushMessageToMQ(mod::MessageString &message) {
    messageQueue->put<std::string>(message.data);
}

void FacadeService::getLoggingServiceData(std::vector<std::string>& msgs) {
    auto serviceChosen = getServiceFromConsul(LOGGING_SERVICE_CONSUL_GET);
    if (!serviceChosen) {
        spdlog::info("Service: No Logging services available");
        return;
    }
    // Send GET to LoggingService
    spdlog::info("Service: Sending GET to: " + serviceChosen->str());
    cpr::Response respLogging = cpr::Get(*serviceChosen);
    spdlog::info("Service: GET STATUS: " + std::to_string(respLogging.status_code));

    std::string loggingMessage = respLogging.text;
    if (respLogging.status_code != 200) {
        loggingMessage = LOGGING_GET_FAIL;
    }

    msgs.push_back(loggingMessage);
}

void FacadeService::getMessageServiceData(std::vector<std::string> &msgs) {
    auto serviceChosen = getServiceFromConsul(MESSAGE_SERVICE_CONSUL_GET);
    if (!serviceChosen) {
        spdlog::info("Service: No Message services available");
        return;
    }
    // Send GET to MessagesService
    spdlog::info("Service: Sending GET to: " + serviceChosen->str());
    cpr::Response respMessages = cpr::Get(*serviceChosen);
    spdlog::info("Service: GET STATUS: " + std::to_string(respMessages.status_code));

    msgs.push_back(respMessages.text);
}
std::optional<cpr::Url> FacadeService::getServiceFromConsul(const std::string& name){
    json response = json::parse(consul.get(name));

    std::vector<std::string> availableServices;
    for (auto & it : response) {
        std::string address = it["ServiceAddress"];
        std::string name = it["ServiceName"];
        int port = it["ServicePort"];
        availableServices.push_back("http://" + address + ":" + std::to_string(port) + "/" + name);
    }

    if (!availableServices.empty()) {
        return {availableServices[rand() % availableServices.size()]};
    }
    return {};
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