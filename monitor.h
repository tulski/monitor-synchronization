#ifndef MONITOR_LABS_MONITOR_H
#define MONITOR_LABS_MONITOR_H

#include <dispatch/dispatch.h>

class Semaphore {
private:
    dispatch_semaphore_t semaphore;

public:
    Semaphore(int value) {
        semaphore = dispatch_semaphore_create(value);

    }

    ~Semaphore() {
        dispatch_release(semaphore);
    }

    void p() {
        dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
    }

    void v() {
        dispatch_semaphore_signal(semaphore);
    }

};

class Condition {
    friend class Monitor;

private:
    Semaphore _semaphore;
    int _waiting;

public:
    Condition() : _semaphore(0) {
        _waiting = 0;
    }

    void bump() {
        ++_waiting;
    }

    void wait() {
        _semaphore.p();
    }

    bool signal() {
        if (_waiting) {
            --_waiting;
            _semaphore.v();
            return true;
        } else
            return false;
    }

};

class Monitor {
private:
    Semaphore _s;

public:
    Monitor() : _s(1) {}

    void enter() {
        _s.p();
    }

    void leave() {
        _s.v();
    }

    void wait(Condition &cond) {
        cond.bump();
        leave();
        cond.wait();
    }

    void signal(Condition &cond) {
        if (cond.signal())
            enter();
    }

};

#endif //MONITOR_LABS_MONITOR_H
