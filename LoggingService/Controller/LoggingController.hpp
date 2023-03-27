#ifndef MICROSERVICES_LOGGINGCONTROLLER_HPP
#define MICROSERVICES_LOGGINGCONTROLLER_HPP

#include <iostream>
#include <random>
#include <sstream>

#include <unordered_map>

#include <spdlog/spdlog.h>
#include <httpserver.hpp>

#include "Service/LoggingService.hpp"

namespace srv {
    using namespace httpserver;

    //! Logging service
    class LoggingController : public http_resource {
        inline static std::string POST_SUCCESS = "Message Logged";
        inline static std::string POST_FAIL = "Message Logged";
    public:
        LoggingController();
        //! Logging GET response
        std::shared_ptr<http_response> render_GET(const http_request& request) override;
        //! Logging POST operations
        std::shared_ptr<http_response> render_POST(const http_request& request) override;

    private:
        LoggingService service;
    };
} // srv

#endif //MICROSERVICES_LOGGINGCONTROLLER_HPP
