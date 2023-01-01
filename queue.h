#ifndef MONITOR_LABS_QUEUE_H
#define MONITOR_LABS_QUEUE_H

#include <vector>

class Queue {
public:
    enum class QueueType {
        LIFO, // Last-In-First-Out (stack)
        FIFO  // First-In-First-Out (queue)
    };

private:
    std::vector<int> queue_;
    QueueType type_;

public:
    // Constructor
    explicit Queue(QueueType type) : type_(type) {}

    int get_element() {
        int element = queue_.back();
        queue_.pop_back();
        return element;
    }

    void add_element(int element) {
        if (type_ == QueueType::FIFO) {
            queue_.insert(queue_.begin(), element);
        } else {
            queue_.push_back(element);
        }
    }

    size_t number_of_elements_() {
        return queue_.size();
    }

};

#endif //MONITOR_LABS_QUEUE_H
