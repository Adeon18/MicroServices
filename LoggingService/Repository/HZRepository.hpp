//
// Created by adeon on 3/27/23.
//

#ifndef MICROSERVICES_HZREPOSITORY_HPP
#define MICROSERVICES_HZREPOSITORY_HPP

#include <memory>

#include <hazelcast/client/hazelcast.h>

#include "MessageUUID.hpp"

class HZRepository {
public:
    explicit HZRepository(const std::string& mapName);
    bool addMessage(const mod::MessageUUID& msg);
    void getMessages(std::vector<mod::MessageUUID>& msgs);
private:
    hazelcast::client::hazelcast_client hzClient;
    std::shared_ptr<hazelcast::client::imap> messagesMap;
};

#endif //MICROSERVICES_HZREPOSITORY_HPP
