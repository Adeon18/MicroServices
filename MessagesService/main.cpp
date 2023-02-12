#include <httpserver.hpp>

static constexpr int SERVICE_PORT = 8082;

using namespace httpserver;

class MessageServiceResource : public http_resource {
    inline static std::string GET_RESPONSE = "Message server GET response placeholder";
public:
    MessageServiceResource() {
        disallow_all();
        set_allowing("GET", true);
    }
    std::shared_ptr<http_response> render_GET(const http_request&) override {
        return std::shared_ptr<http_response>(new string_response(GET_RESPONSE));
    }
};


int main(int argc, char** argv) {
    webserver ws = create_webserver(SERVICE_PORT);

    MessageServiceResource hwr{};
    ws.register_resource("/MessagesService", &hwr);
    ws.start(true);

    return 0;
}