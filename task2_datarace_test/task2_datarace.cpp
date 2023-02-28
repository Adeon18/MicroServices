#include <iostream>
#include <vector>
#include <thread>

#include <hazelcast/client/hazelcast.h>

// 0 - no block; 1 - pessimistic; 2 - optimistic
enum BLOCK_TYPES {
    NONE,
    PESSIMISTIC,
    OPTIMISTIC
};

using namespace hazelcast::client;

static constexpr std::string KEY = "1";

//! Put value, get, increment and put again, repeat 100 times, no locks => datarace
void task2_datarace(int threadNum) {
    hazelcast::client::client_config config;
    config.get_logger_config().level(hazelcast::logger::level::off); // disables logging completely
    auto hz = hazelcast::new_client(std::move(config)).get();
    auto map = hz.get_map("my-distributed-map").get();

    map->put<std::string, int>(KEY, 0).get();
    for (size_t i = 0; i < 1000; ++i) {
        auto val = map->get<std::string, int>(KEY).get();
        ++(*val);
        map->put<std::string, int>(KEY, *val).get();
        //if (i == 500) std::cout << "Thread " << threadNum << ": Wrote half of the values(500)" << std::endl;
    }
    hz.shutdown().get();
}

//! Put value, get, increment and put again, repeat 100 times, pessimistic lock => no datarace
void task2_pessimistic_lock(int threadNum) {
    hazelcast::client::client_config config;
    config.get_logger_config().level(hazelcast::logger::level::off); // disables logging completely
    auto hz = hazelcast::new_client(std::move(config)).get();
    auto map = hz.get_map("my-distributed-map").get();

    map->put<std::string, int>(KEY, 0).get();
    for (size_t i = 0; i < 1000; ++i) {
        // lock
        map->lock(KEY).get();
        try {
            auto val = map->get<std::string, int>(KEY).get();
            ++(*val);
            map->put<std::string, int>(KEY, *val).get();
            //if (i == 500) std::cout << "Thread " << threadNum << ": Wrote half of the values(500)" << std::endl;
        } catch (...) {}
        // unlock
        map->unlock(KEY).get();
    }
    hz.shutdown().get();
}

void task2_optimistic_lock(int threadNum) {
    hazelcast::client::client_config config;
    config.get_logger_config().level(hazelcast::logger::level::off); // disables logging completely
    auto hz = hazelcast::new_client(std::move(config)).get();
    auto map = hz.get_map("my-distributed-map").get();

    map->put<std::string, int>(KEY, 0).get();
    for (size_t i = 0; i < 1000; ++i) {
        while (true) {
            auto valPrev = map->get<std::string, int>(KEY).get();
            int valNew = *valPrev;
            ++valNew;
            if (map->replace<std::string, int>(KEY, *valPrev, valNew).get()) {
                //if (i == 500) std::cout << "Thread " << threadNum << ": Wrote half of the values(500)" << std::endl;
                break;
            }
        }
    }
    hz.shutdown().get();
}

int main() {
    //! Set this variable to the desired block type
    BLOCK_TYPES blockType = BLOCK_TYPES::NONE;

    std::vector<std::thread> threads;

    std::cout << "Starting threads..." << std::endl;

    // Launch 3 threads with the chosen blockType
    for (size_t i = 0; i < 3; i++) {
        std::cout << "Thread " << i << " Started" << std::endl;
        switch(blockType) {
            case BLOCK_TYPES::NONE:
                threads.emplace_back(task2_datarace, i);
                break;
            case BLOCK_TYPES::PESSIMISTIC:
                threads.emplace_back(task2_pessimistic_lock, i);
                break;
            case BLOCK_TYPES::OPTIMISTIC:
                threads.emplace_back(task2_optimistic_lock, i);
                break;
        }
    }

    // Join all the threads
    for (size_t i = 0; i < 3; i++) {
        threads[i].join();
        std::cout << "Thread " << i << " Finished" << std::endl;
    }

    // Get the result, 3000 is the correct one!
    hazelcast::client::client_config config;
    config.get_logger_config().level(hazelcast::logger::level::off); // disables logging completely
    auto hz = hazelcast::new_client(std::move(config)).get();
    auto map = hz.get_map("my-distributed-map").get();
    std::cout << "Finished! Result = " << (*(map->get<std::string, int>("1").get())) << std::endl;
    hz.shutdown().get();

    std::cout << "Done" << std::endl;
    return 0;
}