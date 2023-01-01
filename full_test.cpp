#include <queue>
#include <thread>
#include "queue.h"
#include "actors.h"
#include "repository.h"

int main() {

    // array with 3 producers and 2 subscribers
    std::thread threads[] = {
            std::move(std::thread(Producer, 11, 800, 6, std::ref(wheel_buffer))),
            std::move(std::thread(Producer, 12, 800, 4, std::ref(wheel_buffer))),
            std::move(std::thread(Subscriber, 13, 800, std::ref(wheel_buffer))),

            std::move(std::thread(Producer, 21, 800, 1, std::ref(body_buffer))),
            std::move(std::thread(Producer, 22, 800, 2, std::ref(body_buffer))),
            std::move(std::thread(Subscriber, 23, 800, std::ref(body_buffer))),

            std::move(std::thread(Producer, 31, 800, 15, std::ref(glass_buffer))),
            std::move(std::thread(Producer, 32, 800, 25, std::ref(glass_buffer))),
            std::move(std::thread(Subscriber, 32, 800, std::ref(glass_buffer)))
    };

    for (auto &thread: threads) {
        thread.join();
    }

    return 0;
}