#include <iostream>
#include "queue.h"

void test(Queue queue) {
    for (int i = 1; i <= 3; i++) {
        std::cout << "Adding " << i << " to queue" << std::endl;
        queue.add_element(i);
    }

    while (queue.number_of_elements_() > 0) {
        std::cout << "Getting element result: " << queue.get_element() << std::endl;
    }
}

int main() {
    std::cout << "Testing FIFO queue" << std::endl;
    Queue fifo(Queue::QueueType::FIFO);
    test(fifo);

    std::cout << "Testing LIFO queue" << std::endl;
    Queue lifo(Queue::QueueType::LIFO);
    test(lifo);

    return 0;
}