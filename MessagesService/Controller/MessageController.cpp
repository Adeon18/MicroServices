#include "MessageController.hpp"

namespace srv {
    std::shared_ptr<http_response> MessageController::render_GET(const httpserver::http_request &request)  {
        spdlog::info(
                "Controller: Received GET from: " + std::string{request.get_requestor()} + ":" +
                std::to_string(request.get_requestor_port())
        );
        return std::shared_ptr<http_response>(new string_response(GET_RESPONSE));
    }
} // srv