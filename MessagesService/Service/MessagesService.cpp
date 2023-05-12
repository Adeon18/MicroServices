#include <spdlog/spdlog.h>
#include "MessagesService.hpp"

MessageService::MessageService(int port): hzClient{hazelcast::new_client().get()}, consul{}, consulAgent{consul},
                                          consulKV{consul} {
    consulAgent.registerService(
        "MessageService",
        ppconsul::agent::kw::name = "MessageService",
        ppconsul::agent::kw::address = "127.0.0.1",
        ppconsul::agent::kw::port = port,
        ppconsul::agent::kw::id = "MessageService" + std::to_string(port)
    );

    std::string mqName = consulKV.get("MQNAME", "DEF");
    if (mqName == "DEF") { spdlog::info("Service: Could not get the MQ by name" ); }
    messageQueue = hzClient.get_queue(mqName).get();
}

void MessageService::pollMQ() {
    auto el = messageQueue->take<std::string>().get();
    if (el) {
        spdlog::info("Service: Pulled element from MQ: " + *el);
        messageRepository.putMessage({*el});
    }
}

void MessageService::getMessages(std::vector<mod::MessageString> &messages) {
    messageRepository.getMessages(messages);
}

