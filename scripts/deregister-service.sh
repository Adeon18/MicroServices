#!/bin/bash

CONSUL_NAME=service-manager

# Deregister service by the id
docker exec -it "${CONSUL_NAME}" consul services deregister -id="${1}"