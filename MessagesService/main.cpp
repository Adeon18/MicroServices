#include <httpserver.hpp>

#include "service/MessageService.hpp"

int main(int argc, char** argv) {
    srv::MessageService<srv::SERVICE_PORT> facadeService;

    srv::MessageServiceResource fsr{};
    facadeService.registerService(&fsr);
    facadeService.start();

    return 0;
}