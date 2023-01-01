#ifndef MONITOR_LABS_REPOSITORY_H
#define MONITOR_LABS_REPOSITORY_H

#include <iomanip>
#include <sstream>
#include <iostream>
#include "buffer.h"

Buffer wheel_buffer("wheel_buffer", 100, 4, Queue::QueueType::LIFO);
Buffer body_buffer("body_buffer", 10, 1, Queue::QueueType::LIFO);
Buffer glass_buffer("glass_buffer", 400, 6, Queue::QueueType::FIFO);
Buffer pedal_buffer("pedal_buffer", 600, 3, Queue::QueueType::FIFO);

enum Color {
    RED = 31,
    GREEN = 32,
    WHITE = 37
};

void log_debug(Color color, std::string message) {
    std::stringstream ss;
    ss << "\033[1;" << color << "m";
    ss << std::left << std::setw(60) << message;
    ss << wheel_buffer.to_string() << "\t";
    ss << body_buffer.to_string() << "\t";
    ss << glass_buffer.to_string() << "\t";
    ss << pedal_buffer.to_string() << "\t";
    ss << "\033[0m\n";
    std::cout << ss.str();
}

#endif //MONITOR_LABS_REPOSITORY_H
