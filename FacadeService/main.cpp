#include <iostream>
#include <httpserver.hpp>
#include <cpr/cpr.h>

#include "service/FacadeService.hpp"


int main(int argc, char** argv) {
    srv::FacadeService<srv::SERVICE_PORT> facadeService;

    srv::FacadeServiceResource fsr{};
    facadeService.registerService(&fsr);
    facadeService.start();

    return 0;
}