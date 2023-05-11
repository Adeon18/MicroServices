#ifndef MICROSERVICES_FACADESERVICE_HPP
#define MICROSERVICES_FACADESERVICE_HPP

#include <vector>
#include <optional>

#include <random>

#include <cpr/cpr.h>

#include <hazelcast/client/hazelcast.h>

#include <ppconsul/agent.h>

#include "MessageUUID.hpp"
#include "MessageString.hpp"


class FacadeService {
    inline static std::string LOGGING_GET_FAIL = "Failed to GET data from a logging service";
    inline static std::string LOGGING_POST_FAIL = "Failed to POST data to logging service";
    inline static std::string LOGGING_SERVICE_CONSUL_GET = "/v1/catalog/service/LoggingService";
public:
    //! Basically pushes all the available logging services
    FacadeService(int port);
    //! Fills the vector with messages from Logging and MessageService
    void getMessages(std::vector<std::string>& messages);
    //! Add UUID to message and send it to Logging Service
    std::optional<std::string> sendMessageToLogging(mod::MessageUUID& message);
    void pushMessageToMQ(mod::MessageString& message);

private:
    void getLoggingServiceData(std::vector<std::string>& msgs);
    void getMessageServiceData(std::vector<std::string>& msgs);
    //! Pull all the logging services from consul and return a url a random one
    [[nodiscard]] std::optional<cpr::Url> getLoggingService();

    std::vector<cpr::Url> loggingServices;
    std::vector<cpr::Url> messageServices;

    ppconsul::Consul consul;
    ppconsul::agent::Agent consulAgent;
    hazelcast::client::hazelcast_client hzClient;
    std::shared_ptr<hazelcast::client::iqueue> messageQueue;
};

namespace util {
    std::string generate_uuid_v4();
}


#endif //MICROSERVICES_FACADESERVICE_HPP
