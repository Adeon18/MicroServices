#ifndef MICROSERVICES_MESSAGEMEMREPOSITORY_HPP
#define MICROSERVICES_MESSAGEMEMREPOSITORY_HPP

#include <vector>
#include <string>

#include "MessageString.hpp"

class MessageMemRepository {
public:
    //! Get the messages from storage into a vector
    void getMessages(std::vector<mod::MessageString>& messages);
    //! Save the message
    void putMessage(const mod::MessageString& msg);
private:
    std::vector<std::string> messagesRepo;
};

#endif //MICROSERVICES_MESSAGEMEMREPOSITORY_HPP
