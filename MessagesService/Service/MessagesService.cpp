#include <spdlog/spdlog.h>
#include "MessagesService.hpp"

MessageService::MessageService(): hzClient{hazelcast::new_client().get()} {
    messageQueue = hzClient.get_queue("MQ").get();
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

