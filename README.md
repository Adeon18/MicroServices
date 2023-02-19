# MicroServices
Some microservices written in C++ as lab works for the Software Architecture Course at Ukrainian Catholic University

## Running via docker

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