#ifndef MICROSERVICES_LOGGINGSERVICE_HPP
#define MICROSERVICES_LOGGINGSERVICE_HPP

#include <vector>

#include "Message.hpp"

#include "../Repository/MemoryRepository.hpp"

class LoggingService {
public:
    LoggingService(): repository{} {}

    bool addMessage(const mod::Message& msg);
    void getMessages(std::vector<mod::Message>& msgs);
private:
    MemoryRepository repository;
};

#endif //MICROSERVICES_LOGGINGSERVICE_HPP
