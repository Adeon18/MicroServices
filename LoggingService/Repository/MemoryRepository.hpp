#ifndef MICROSERVICES_MEMORYREPOSITORY_HPP
#define MICROSERVICES_MEMORYREPOSITORY_HPP

#include <vector>
#include <unordered_map>

#include "MessageUUID.hpp"

class MemoryRepository {
public:
    MemoryRepository(){}
    bool addMessage(const mod::MessageUUID& msg);
    void getMessages(std::vector<mod::MessageUUID>& msgs);
private:
    std::unordered_map<std::string, std::string> messageMap;
};

#endif //MICROSERVICES_MEMORYREPOSITORY_HPP
