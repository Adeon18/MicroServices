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

Hazelcast Cluster:
```sh
# 3 hazelcast nodes in docker - wait for them to connect
docker run -p 5701:5701 hazelcast/hazelcast
docker run -p 5702:5701 hazelcast/hazelcast
docker run -p 5703:5701 hazelcast/hazelcast
```

To Run Consul:
```shell
./scripts/run-consul.sh
```

To Fill Key/Value data in Consul:
```shell
./scripts/fill-data.sh
```

Microservices:
```shell
./FacadeService/FacadeService <port>
./LoggingService/LoggingService <port>
./MessagesService/MessagesService <port>
```
- Can run multiple services, and they will register themselves to consul at start.


To deregister service in Consul at halt:
```shell
./scripts/deregister-service.sh <service-id>
```

To shutdown and delete consul container:
```shell
./stop-consul.sh
```