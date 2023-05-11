#ifndef MICROSERVICES_LOGGINGSERVICE_HPP
#define MICROSERVICES_LOGGINGSERVICE_HPP

#include <vector>

#include <ppconsul/agent.h>

#include "MessageUUID.hpp"

#include "../Repository/MemoryRepository.hpp"
#include "../Repository/HZRepository.hpp"

#define HZ_MAP_ENABLE 1

class LoggingService {
public:
    explicit LoggingService(int port): repository{}, consul{}, consulAgent{consul} {
        consulAgent.registerService(
                "LoggingService",
                ppconsul::agent::kw::name = "LoggingService",
                ppconsul::agent::kw::address = "127.0.0.1",
                ppconsul::agent::kw::port = port,
                ppconsul::agent::kw::id = "LoggingService" + std::to_string(port)
                //ppconsul::agent::kw::check = ppconsul::agent::HttpCheck{"http://127.0.0.1:8080/FacadeService", std::chrono::seconds(2)}
        );
    }

    bool addMessage(const mod::MessageUUID& msg);
    void getMessages(std::vector<mod::MessageUUID>& msgs);
private:
#if HZ_MAP_ENABLE == 1
    HZRepository repository;
    ppconsul::Consul consul;
    ppconsul::agent::Agent consulAgent;
#else
    MemoryRepository repository;
#endif
};

#endif //MICROSERVICES_LOGGINGSERVICE_HPP
