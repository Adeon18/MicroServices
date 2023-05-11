#include <iostream>

#include <cpr/cpr.h>

#include "FacadeController.hpp"

namespace srv {
    FacadeController::FacadeController(int port): facadeService{port} {
        disallow_all();
        set_allowing("GET", true);
        set_allowing("POST", true);
    }
    std::shared_ptr<http_response> FacadeController::render_GET(const http_request& request) {
        spdlog::info("Controller: Received GET from: " + std::string{request.get_requestor()} + ":" + std::to_string(request.get_requestor_port()));

        std::vector<std::string> responseVec;
        facadeService.getMessages(responseVec);

        std::string response;
        for (auto& msg: responseVec) {
            response += msg + '|';
        }

        return std::shared_ptr<http_response>(new string_response(response));
    }

    std::shared_ptr<http_response> FacadeController::render_POST(const http_request& request) {
        spdlog::info("Controller: Received POST from: " + std::string{request.get_requestor()} + ":" + std::to_string(request.get_requestor_port()));

        mod::MessageUUID msg{"", std::string{request.get_content()}};
        mod::MessageString msgStr{std::string{request.get_content()}};

        std::optional<std::string> serviceResponse = facadeService.sendMessageToLogging(msg);
        facadeService.pushMessageToMQ(msgStr);

        return std::shared_ptr<http_response>(new string_response((serviceResponse) ? POST_SUCCESS: POST_FAILURE));
    }
} // srv