#!/bin/bash
CONSUL_NAME=service-manager
MQ_K_NAME="MQNAME"
MQ_V_NAME="MQ"

MAP_K_NAME="MAPNAME"
MAP_V_NAME="my-distributed-map"

docker exec -it "${CONSUL_NAME}" consul kv put "${MQ_K_NAME}" "${MQ_V_NAME}"

docker exec -it "${CONSUL_NAME}" consul kv put "${MAP_K_NAME}" "${MAP_V_NAME}"