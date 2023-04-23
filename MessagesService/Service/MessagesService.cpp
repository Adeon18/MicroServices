#include "MessagesService.hpp"

MessageService::MessageService(): hzClient{hazelcast::new_client().get()} {
    messageQueue = hzClient.get_queue("MQ").get();
}

void MessageService::pollMQ() {
    std::cout << messageQueue->take<std::string>().get() << std::endl;
}

void MessageService::getMessages(std::vector<mod::MessageString> &messages) {

}

