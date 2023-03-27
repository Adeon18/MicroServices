# MicroServices
- By [Ostap Trush](https://github.com/Adeon18)

Some microservices written in C++ as lab works for the Software Architecture Course at Ukrainian Catholic University

## Requirements
- gcc/clang
- cmake
- spdlog
- libhttpserver
- cpr
- [hazelcast c++ client](https://github.com/hazelcast/hazelcast-cpp-client)

_Note: cpr, spdlog and libhttpserver can be installed via package managers or by compiling from
source(the libraries are connected as submodules)_

_Note 2: Hazelcast C++ Client has to be installed manually_

## Building

```
git clone https://github.com/Adeon18/MicroServices.git

git submodule init      # If building libraries from scratch
git submodule update    # if building libraries from scratch

cd MicroServices
mkdir build && cd build
cmake .. && make
```

## Running

```sh
# 2 basic services(port 8080 and 8081)
./FacadeService/FacadeService
./MessageService/MessageService

# 3 hazelcast nodes in docker - wait for them to connect
docker run -p 5701:5701 hazelcast/hazelcast
docker run -p 5702:5701 hazelcast/hazelcast
docker run -p 5703:5701 hazelcast/hazelcast

# 3 Logging services to work with 3 nodes
./LoggingService/LoggingService 8082
./LoggingService/LoggingService 8083
./LoggingService/LoggingService 8084
```