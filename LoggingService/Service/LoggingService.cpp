//
// Created by adeon on 3/27/23.
//
#include "LoggingService.hpp"


bool LoggingService::addMessage(const mod::Message &msg) {
    return repository.addMessage(msg);
}

void LoggingService::getMessages(std::vector<mod::Message> &msgs) {
    repository.getMessages(msgs);
}

