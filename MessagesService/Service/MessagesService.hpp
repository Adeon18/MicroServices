#ifndef MICROSERVICES_MESSAGESSERVICE_HPP
#define MICROSERVICES_MESSAGESSERVICE_HPP

#include <vector>
#include <hazelcast/client/hazelcast.h>

#include "MessageString.hpp"

class MessageService {
public:
    MessageService();
    //! Fill the passed vector with messages from Repository
    void getMessages(std::vector<mod::MessageString>& messages);
    //! Poll the hazelcast MQ for messages, should be called in a loop
    void pollMQ();
private:
    hazelcast::client::hazelcast_client hzClient;
    std::shared_ptr<hazelcast::client::iqueue> messageQueue;
};

#endif //MICROSERVICES_MESSAGESSERVICE_HPP
