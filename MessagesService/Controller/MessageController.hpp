#ifndef MICROSERVICES_MESSAGECONTROLLER_HPP
#define MICROSERVICES_MESSAGECONTROLLER_HPP

#include <iostream>
#include <random>
#include <sstream>

#include <unordered_map>

#include <spdlog/spdlog.h>
#include <httpserver.hpp>

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
        std::shared_ptr<http_response> render_GET(const http_request& request) override {
            spdlog::info(
                    "Controller: Received GET from: " + std::string{request.get_requestor()} + ":" +
                        std::to_string(request.get_requestor_port())
            );
            return std::shared_ptr<http_response>(new string_response(GET_RESPONSE));
        }
    };
} // srv

#endif //MICROSERVICES_MESSAGECONTROLLER_HPP
