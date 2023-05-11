CONSUL_NAME=service-manager

docker stop "${CONSUL_NAME}"
docker rm "${CONSUL_NAME}"
