//
// Created by adeon on 3/27/23.
//
#include <spdlog/spdlog.h>

#include "HZRepository.hpp"

HZRepository::HZRepository(const std::string& mapName): hzClient{hazelcast::new_client().get()} {
    messagesMap = hzClient.get_map(mapName).get();
}

bool HZRepository::addMessage(const mod::MessageUUID &msg) {
    messagesMap->put<std::string, std::string>(msg.uuid, msg.text).get();
    spdlog::info("Repository: Message logged: " + msg.toString()) ;
    return true;
}

void HZRepository::getMessages(std::vector<mod::MessageUUID> &msgs) {
    for (const auto &entry : messagesMap->entry_set<std::string, std::string>().get()) {
        msgs.emplace_back(entry.first, entry.second);
    }
}

