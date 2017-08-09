#ifndef SPIDER_CORE_TASK_HPP
#define SPIDER_CORE_TASK_HPP

#include <thread>
#include <functional>
#include <future>
#include <list>
#include <queue>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <iostream>
#include <assert.h>

namespace spider {
namespace core {

class Task {
public:
    Task(std::function<void()> func = nullptr);
    void Cancel();
    void Run();

private:
    std::function<void()> func_;
    bool is_cancelled_;
    bool is_completed_;
};


class TaskQueue: public std::queue<Task> {
public:
    void Swap(TaskQueue* dest_queue);
};

}
}

#endif
