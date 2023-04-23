#include "MessageMemRepository.hpp"

void MessageMemRepository::getMessages(std::vector<mod::MessageString> &messages) {
    for (auto& msg: messagesRepo) {
        messages.emplace_back(msg);
    }
}

void MessageMemRepository::putMessage(const mod::MessageString &msg) {
    messagesRepo.emplace_back(msg.data);
}

