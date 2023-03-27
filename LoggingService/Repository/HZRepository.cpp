//
// Created by adeon on 3/27/23.
//
#include <spdlog/spdlog.h>

#include "HZRepository.hpp"

//HZRepository::HZRepository()  {
////        hazelcast::client::client_config config;
////        config.get_logger_config().level(hazelcast::logger::level::off); // disables logging completely
//}

bool HZRepository::addMessage(const mod::Message &msg) {
    messagesMap->put<std::string, std::string>(msg.uuid, msg.text).get();
    spdlog::info("Repository: Message logged: " + msg.toString()) ;
    return true;
}

void HZRepository::getMessages(std::vector<mod::Message> &msgs) {
    for (const auto &entry : messagesMap->entry_set<std::string, std::string>().get()) {
        msgs.emplace_back(entry.first, entry.second);
    }
}

