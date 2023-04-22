#ifndef MICROSERVICES_LOGGINGSERVICE_HPP
#define MICROSERVICES_LOGGINGSERVICE_HPP

#include <vector>

#include "MessageUUID.hpp"

#include "../Repository/MemoryRepository.hpp"
#include "../Repository/HZRepository.hpp"

#define HZ_MAP_ENABLE 1

class LoggingService {
public:
    LoggingService(): repository{} {}

    bool addMessage(const mod::MessageUUID& msg);
    void getMessages(std::vector<mod::MessageUUID>& msgs);
private:
#if HZ_MAP_ENABLE == 1
    HZRepository repository;
#else
    MemoryRepository repository;
#endif
};

#endif //MICROSERVICES_LOGGINGSERVICE_HPP
