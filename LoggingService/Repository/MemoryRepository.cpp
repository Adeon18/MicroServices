//
// Created by adeon on 3/27/23.
//
#include <spdlog/spdlog.h>

#include "MemoryRepository.hpp"

bool MemoryRepository::addMessage(const mod::MessageUUID& msg) {
    messageMap[msg.uuid] = msg.text;
    spdlog::info("Repository: Message logged: " + msg.toString()) ;
    return true;
}

void MemoryRepository::getMessages(std::vector<mod::MessageUUID> &msgs) {
    for (auto& [uuid, text]: messageMap) {
        msgs.emplace_back(uuid, text);
    }
}

