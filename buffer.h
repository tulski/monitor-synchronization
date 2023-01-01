#ifndef MONITOR_LABS_BUFFER_H
#define MONITOR_LABS_BUFFER_H


#include <mutex>
#include "queue.h"
#include "monitor.h"

class Buffer:Monitor {

private:
    // Name of the buffer
    std::string name_;

    // Maximum capacity of the buffer
    int capacity_;

    // Number of elements returned when retrieving from the buffer
    int retrieve_elements_count;

    Condition full;
    Condition empty;

    // Queue containing the elements
    Queue queue_;

public:
    // Constructor
    Buffer(std::string name, int capacity, int numReturned, Queue::QueueType type)
            : name_(std::move(name)), capacity_(capacity), queue_(Queue(type)), retrieve_elements_count(numReturned) {
    }

    // insert an element into the buffer
    void insert(std::vector<int> elements) {
        enter();

        if (queue_.number_of_elements_() + elements.size() > capacity_) {
            wait(full);
        }

        // Add the element to the queue depending on its type
        for (auto &element: elements) {
            queue_.add_element(element);
        }

        if (queue_.number_of_elements_() >= retrieve_elements_count) {
            signal(empty);
        }

        // Signal that a new element has been received
        leave();
    }

    // retrieve an element from the buffer
    std::vector<int> retrieve() {
        enter();

        // protect access to the queue

        if (queue_.number_of_elements_() < retrieve_elements_count) {
            wait(empty);
        }

        // retrieve the specified number of elements
        std::vector<int> retrieved;
        for (int i = 0; i < retrieve_elements_count; ++i) {
            retrieved.push_back(queue_.get_element());
        }


        // signal that elements have been retrieved
        leave();

        return retrieved;
    }

    std::string to_string() {
        return name_ + " - " + std::to_string(queue_.number_of_elements_()) + "/" + std::to_string(capacity_);
    }

    std::string get_name() {
        return name_;
    }

};

#endif //MONITOR_LABS_BUFFER_H
