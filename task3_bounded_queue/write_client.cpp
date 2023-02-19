#include <iostream>

#include <hazelcast/client/hazelcast.h>

using namespace hazelcast::client;

int main() {

    auto hz = hazelcast::new_client().get();
    auto queue = hz.get_queue("queue").get();

    for (size_t i = 0; i < 10; ++i) {
        queue->put<int>(i).get();
        std::cout << "Put element " << i << std::endl;
    }

    hz.shutdown().get();
    std::cout << "Done" << std::endl;
    return 0;
}