#ifndef MICROSERVICES_MESSAGESSERVICE_HPP
#define MICROSERVICES_MESSAGESSERVICE_HPP

#include <vector>
#include <hazelcast/client/hazelcast.h>

#include <ppconsul/agent.h>
#include <ppconsul/kv.h>

#include "MessageString.hpp"
#include "../Repository/MessageMemRepository.hpp"

class MessageService {
public:
    MessageService(int port);
    //! Fill the passed vector with messages from Repository
    void getMessages(std::vector<mod::MessageString>& messages);
    //! Poll the hazelcast MQ for messages, should be called in a loop
    void pollMQ();
private:
    ppconsul::Consul consul;
    ppconsul::agent::Agent consulAgent;
    ppconsul::kv::Kv consulKV;
    MessageMemRepository messageRepository;
    hazelcast::client::hazelcast_client hzClient;
    std::shared_ptr<hazelcast::client::iqueue> messageQueue;
};

#endif //MICROSERVICES_MESSAGESSERVICE_HPP
