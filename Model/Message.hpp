#ifndef MICROSERVICES_MESSAGE_HPP
#define MICROSERVICES_MESSAGE_HPP

#include <string>

namespace mod {
    struct Message {
        std::string uuid;
        std::string text;

        [[nodiscard]] std::string toString() const { return "[" + uuid + ", " + text + "]"; }
    };
} // mod

#endif //MICROSERVICES_MESSAGE_HPP
