#ifndef MICROSERVICES_MEMORYREPOSITORY_HPP
#define MICROSERVICES_MEMORYREPOSITORY_HPP

#include <vector>
#include <unordered_map>

#include "Message.hpp"

class MemoryRepository {
public:
    MemoryRepository(){}
    bool addMessage(const mod::Message& msg);
    void getMessages(std::vector<mod::Message>& msgs);
private:
    std::unordered_map<std::string, std::string> messageMap;
};

#endif //MICROSERVICES_MEMORYREPOSITORY_HPP
