#include "LoggingController.hpp"

namespace srv {
    LoggingController::LoggingController(): service{} {
        disallow_all();
        set_allowing("GET", true);
        set_allowing("POST", true);
    }

    std::shared_ptr<http_response> LoggingController::render_GET(const http_request& request) {
        spdlog::info(
                "Controller: Received GET from: " + std::string{request.get_requestor()} + ":" +
                std::to_string(request.get_requestor_port())
        );
        // Get all the messages from the map
        std::vector<mod::MessageUUID> msgs;
        service.getMessages(msgs);

        std::string messagesString;
        for (auto& msg: msgs) {
            messagesString += msg.text + " ";
        }

        spdlog::info("Controller: GET response: " + messagesString);

        return std::shared_ptr<http_response>(new string_response(messagesString));
    }

    std::shared_ptr<http_response> LoggingController::render_POST(const http_request& request) {
        spdlog::info(
                "Controller: Received POST from: " + std::string{request.get_requestor()} + ":" +
                std::to_string(request.get_requestor_port())
        );

        // Push the pair into the map
        bool success = false;
        const auto argsMap = request.get_args();
        // This is always 1 iteration for now
        for (auto& [uuid, text]: argsMap) {
            std::string strUUID = std::string{uuid};
            std::string strText = std::string{text};

            success = service.addMessage({strUUID, strText});
        }

        return std::shared_ptr<http_response>(new string_response((success) ? POST_SUCCESS: POST_FAIL));
    }
} // srv