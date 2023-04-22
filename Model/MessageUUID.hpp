#ifndef MICROSERVICES_MESSAGEUUID_HPP
#define MICROSERVICES_MESSAGEUUID_HPP

#include <string>

namespace mod {
    struct MessageUUID {
        std::string uuid;
        std::string text;

        [[nodiscard]] std::string toString() const { return "[" + uuid + ", " + text + "]"; }
    };
} // mod

#endif //MICROSERVICES_MESSAGEUUID_HPP
