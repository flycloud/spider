#ifndef SPIDER_CORE_THREAD_HPP
#define SPIDER_CORE_THREAD_HPP

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
#include <spider/core/include/task.hpp>

namespace spider {
namespace core {

class ThreadBase {
public:
    ThreadBase();
    virtual ~ThreadBase();
    void Start();
    void Stop();
    bool PostTask(std::function<void()>&& func);
    bool PostTask(const Task& task);

private:
    void ReloadWorkingQueue();
    void DoRun();

private:
    bool is_initialized_;
    bool is_running_;
    std::unique_ptr<std::thread> thread_;
    TaskQueue working_queue_;
    TaskQueue incoming_queue_;
    std::mutex incoming_queue_mutex_;
    std::condition_variable incoming_queue_cond_;
};

}
}

#endif
