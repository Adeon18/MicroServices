#include <iostream>

#include <hazelcast/client/hazelcast.h>

using namespace hazelcast::client;

//! Put 1000 elements into the map
void task1(hazelcast_client& hz, const std::shared_ptr<imap>& map) {
    for (size_t i = 0; i < 1000; ++i) {
        map->put<std::string, int>("key_" + std::to_string(i), i).get();
    }
}

int main() {

    auto hz = hazelcast::new_client().get();
    auto map = hz.get_map("my-distributed-map").get();

    task1(hz, map);

    hz.shutdown().get();
    std::cout << "Done" << std::endl;
    return 0;
}