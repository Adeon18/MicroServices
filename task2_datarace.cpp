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
void task2_datarace(const std::shared_ptr<imap>& map) {
    map->put<std::string, int>(KEY, 0).get();
    for (size_t i = 0; i < 1000; ++i) {
        auto val = map->get<std::string, int>(KEY).get();
        ++(*val);
        map->put<std::string, int>(KEY, *val).get();
    }
}

//! Put value, get, increment and put again, repeat 100 times, pessimistic lock => no datarace
void task2_pessimistic_lock(const std::shared_ptr<imap>& map) {
    map->put<std::string, int>(KEY, 0).get();
    for (size_t i = 0; i < 1000; ++i) {
        // lock
        map->lock(KEY).get();
        try {
            auto val = map->get<std::string, int>(KEY).get();
            ++(*val);
            map->put<std::string, int>(KEY, *val).get();
        } catch (...) {}
        // unlock
        map->unlock(KEY).get();
    }
}

void task2_optimistic_lock(const std::shared_ptr<imap>& map) {
    map->put<std::string, int>(KEY, 0).get();
    for (size_t i = 0; i < 1000; ++i) {
        while (true) {
            auto valPrev = map->get<std::string, int>(KEY).get();
            int valNew = *valPrev;
            ++valNew;
            if (map->replace<std::string, int>(KEY, *valPrev, valNew).get()) {
                break;
            }
        }
    }
}

int main() {

    //! Set this variable to the desired block type
    BLOCK_TYPES blockType = BLOCK_TYPES::OPTIMISTIC;

    auto hz = hazelcast::new_client().get();
    auto map = hz.get_map("my-distributed-map").get();

    std::vector<std::thread> threads;

    std::cout << "Starting threads..." << std::endl;

    // Launch 3 threads with the chosen blockType
    for (size_t i = 0; i < 3; i++) {
        switch(blockType) {
            case BLOCK_TYPES::NONE:
                threads.emplace_back(task2_datarace, std::ref(map));
                break;
            case BLOCK_TYPES::PESSIMISTIC:
                threads.emplace_back(task2_pessimistic_lock, std::ref(map));
                break;
            case BLOCK_TYPES::OPTIMISTIC:
                threads.emplace_back(task2_optimistic_lock, std::ref(map));
                break;
        }
    }

    // Join all the threads
    for (size_t i = 0; i < 3; i++) {
        threads[i].join();
        std::cout << "Thread " << i << " Finished" << std::endl;
    }

    // Get the result, 3000 is the correct one!
    std::cout << "Finished! Result = " << (*(map->get<std::string, int>("1").get())) << std::endl;

    hz.shutdown().get();

    std::cout << "Done" << std::endl;
    return 0;
}