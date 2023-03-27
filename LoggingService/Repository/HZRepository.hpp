//
// Created by adeon on 3/27/23.
//

#ifndef MICROSERVICES_HZREPOSITORY_HPP
#define MICROSERVICES_HZREPOSITORY_HPP

#include <memory>

#include <hazelcast/client/hazelcast.h>

#include "Message.hpp"

class HZRepository {
public:
    HZRepository();
    bool addMessage(const mod::Message& msg);
    void getMessages(std::vector<mod::Message>& msgs);
private:
    hazelcast::client::hazelcast_client hzClient;
    std::shared_ptr<hazelcast::client::imap> messagesMap;
};

#endif //MICROSERVICES_HZREPOSITORY_HPP
