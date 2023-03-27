#ifndef MICROSERVICES_FACADESERVICE_HPP
#define MICROSERVICES_FACADESERVICE_HPP

#include <vector>

#include <random>

#include <cpr/cpr.h>

#include "Message.hpp"

class FacadeService {
    inline static std::string MESSAGES_SERVICE_ADDRESS = "http://localhost:8082/MessageService";
    inline static std::string LOGGING_SERVICE_ADDRESS = "http://localhost:8081/LoggingService";
public:
    //! Fills the vector with messages from Logging and MessageService
    void getMessages(std::vector<std::string>& messages);
    //! Add UUID to message and send it to Logging Service
    cpr::Response sendMessage(mod::Message& message);
private:
};

namespace util {
    std::string generate_uuid_v4();
}


#endif //MICROSERVICES_FACADESERVICE_HPP
