#ifndef MICROSERVICES_FACADECONTROLLER_HPP
#define MICROSERVICES_FACADECONTROLLER_HPP

#include <random>
#include <sstream>

#include <httpserver.hpp>
#include <spdlog/spdlog.h>

#include "../Service/FacadeService.hpp"

namespace srv {
    using namespace httpserver;
    //! Facade Service Resourse
    class FacadeController : public http_resource {
        inline static std::string MESSAGES_SERVICE_ADDRESS = "http://localhost:8081/MessageService";
        inline static std::string LOGGING_SERVICE_ADDRESS = "http://localhost:8082/LoggingService";

        inline static std::string POST_SUCCESS = "Posted to Message and Logging services";
        inline static std::string POST_FAILURE = "Failed posting to Message and Logging services";
    public:
        FacadeController();

        //! Send get requests to MessageService and Logging Service and return respective data
        std::shared_ptr<http_response> render_GET(const http_request &request) override;
        //! Generate UUID and send a post request to Logging Service
        std::shared_ptr<http_response> render_POST(const http_request &request) override;
    private:
        FacadeService facadeService;
    };
} // srv

#endif //MICROSERVICES_FACADECONTROLLER_HPP
