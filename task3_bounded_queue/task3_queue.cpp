#include <iostream>
#include <chrono>

#include <hazelcast/client/hazelcast.h>

using namespace hazelcast::client;

//! Write N elements into a queue
void write_client(int threadNum) {
    auto hz = hazelcast::new_client().get();
    auto queue = hz.get_queue("queue").get();

    for (size_t i = 0; i < 10; ++i) {
        queue->put<int>(i).get();
        std::cout << "Thread Write " << threadNum << ": Put element " << i << std::endl;
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    hz.shutdown().get();
}

//! Read N elements into a queue
void read_client(int threadNum) {
    auto hz = hazelcast::new_client().get();
    auto queue = hz.get_queue("queue").get();

    for (size_t i = 0; i < 5; ++i) {
        auto el = queue->take<int>().get();
        std::cout << "Thread Read " << threadNum << ": Took element " << el << std::endl;
        //std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    hz.shutdown().get();
}

//! You can just comment and uncomment the respective reading/writing threads
int main() {
    std::vector<std::thread> threads;

    std::cout << "Starting threads..." << std::endl;

    std::thread write_thread{write_client, 1};

    std::thread read_thread1{read_client, 1};
    std::thread read_thread2{read_client, 2};

    write_thread.join();

    read_thread1.join();
    read_thread2.join();

    std::cout << "Done" << std::endl;
    return 0;
}