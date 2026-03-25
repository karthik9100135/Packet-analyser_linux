#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class BoundedQueue {
private:
    std::queue<T> q;
    std::mutex m;
    std::condition_variable cv;
    size_t capacity;

public:
    BoundedQueue(size_t cap) : capacity(cap) {}

    void push(const T& item) {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [&]() { return q.size() < capacity; });
        q.push(item);
        cv.notify_all();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [&]() { return !q.empty(); });
        T item = q.front();
        q.pop();
        cv.notify_all();
        return item;
    }
};
