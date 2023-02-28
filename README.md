# Lab 2 - hazelcast testing
- By [Ostap Trush](https://github.com/Adeon18)


## Requirements
- gcc/clang
- cmake

## Building

Ths will build 3 different executables for 3 different tasks.

You are free to modify the code as suggested in the comments to achieve
the results specified in the protocol.

```
git clone https://github.com/Adeon18/MicroServices.git

cd MicroServices
mkdir build && cd build
cmake .. && make
```

## Running the HZ via docker

### Run the cluster nodes
```sh
docker run -p 5701:5701 hazelcast/hazelcast
```
Then you **preferably** increment the host port for each new node.

### Run the management service
```sh
docker run -p 8080:8080 hazelcast/management-center
```

### Run the cluster nodes via config file in some directory

Same as for t:
```sh
cd task3_bounded_queue
docker run -v "$(pwd)"/hazelcast.yml:/opt/hazelcast/hazelcast.yml -e HAZELCAST_CONFIG=hazelcast.yml -p:5701:5701 hazelcast/hazelcast
```