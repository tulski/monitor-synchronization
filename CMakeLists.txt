cmake_minimum_required(VERSION 3.23)
project(monitor_labs)

set(CMAKE_CXX_STANDARD 20)

add_executable(queue_test queue_test.cpp queue.h)
add_executable(full_test full_test.cpp queue.h buffer.h actors.h repository.h monitor.h)
add_executable(simple_test simple_test.cpp queue.h buffer.h actors.h repository.h)