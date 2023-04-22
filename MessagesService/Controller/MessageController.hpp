#ifndef MICROSERVICES_MESSAGECONTROLLER_HPP
#define MICROSERVICES_MESSAGECONTROLLER_HPP

#include <iostream>
#include <random>
#include <sstream>

#include <unordered_map>

#include <spdlog/spdlog.h>
#include <httpserver.hpp>

#include "../Service/MessagesService.hpp"

namespace srv {
    using namespace httpserver;

    //! Logging service
    class MessageController : public http_resource {
        inline static std::string GET_RESPONSE = "Message server GET response placeholder";
    public:
        MessageController() {
            disallow_all();
            set_allowing("GET", true);
        }
        std::shared_ptr<http_response> render_GET(const http_request& request) override;
    private:
        MessageService messageService;
    };
} // srv

#endif //MICROSERVICES_MESSAGECONTROLLER_HPP
