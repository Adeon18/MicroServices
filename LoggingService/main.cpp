#include <iostream>

#include "service/LoggingService.hpp"

int main() {
    srv::LoggingService<srv::SERVICE_PORT> loggingService;

    srv::LoggingServiceResource lsr{};
    loggingService.registerService(&lsr);
    loggingService.start();

    return 0;
}
