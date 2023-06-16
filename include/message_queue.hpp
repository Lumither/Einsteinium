#ifndef MESSAGE_QUEUE_HPP
#define MESSAGE_QUEUE_HPP

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>

template<typename msg_t>
class MessageQueue {
private:
    std::mutex mtx;
    std::condition_variable cond_var;
    std::queue<msg_t> msg_queue;

public:
    auto push(const msg_t &msg) -> void {
        std::unique_lock<std::mutex> lck(mtx);
        msg_queue.push(msg);
        lck.unlock();
        cond_var.notify_one();
    }

    auto pop() -> msg_t {
        std::unique_lock<std::mutex> lck(mtx);
        cond_var.wait(lck, [this]() {
            return !msg_queue.empty();
        });
        auto msg = msg_queue.front();
        msg_queue.pop();
        lck.unlock();
        return msg;
    }
};

#endif