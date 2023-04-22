//
// Created by adeon on 3/27/23.
//
#include "LoggingService.hpp"


bool LoggingService::addMessage(const mod::MessageUUID &msg) {
    return repository.addMessage(msg);
}

void LoggingService::getMessages(std::vector<mod::MessageUUID> &msgs) {
    repository.getMessages(msgs);
}

