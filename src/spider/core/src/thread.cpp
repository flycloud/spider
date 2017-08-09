#include <spider/core/include/thread.hpp>

namespace spider {
namespace core {

ThreadBase::ThreadBase()
: is_initialized_(false), is_running_(false) {

}

ThreadBase::~ThreadBase() {
    Stop();
}

void ThreadBase::Start() {
    if (is_initialized_)
        return;

    is_initialized_ = true;

    thread_.reset(new std::thread([this] {
        this->is_running_ = true;
        this->DoRun();
    }));
}


void ThreadBase::Stop() {
    std::cout<<"Stop enter"<<std::endl;
    if (!is_initialized_ || !is_running_)
        return;

    is_running_ = false;
    incoming_queue_cond_.notify_all();
    if (thread_->joinable()) {
        thread_->join();
    }
    thread_.reset();

    is_initialized_ = false;
    std::cout<<"Stop leave"<<std::endl;
}

bool ThreadBase::PostTask(std::function<void()>&& func) {
    if (!is_initialized_)
        return false;

    std::lock_guard<std::mutex> lock(incoming_queue_mutex_);
    Task task(func);
    incoming_queue_.emplace(std::move(task));
    incoming_queue_cond_.notify_all();
    return true;
}

bool ThreadBase::PostTask(const Task& task) {
    if (!is_initialized_)
        return false;

    std::lock_guard<std::mutex> lock(incoming_queue_mutex_);
    incoming_queue_.emplace(std::move(task));
    incoming_queue_cond_.notify_all();
    return true;
}

void ThreadBase::ReloadWorkingQueue() {
    assert(working_queue_.empty());

    std::unique_lock<std::mutex> lock(incoming_queue_mutex_);
    if (incoming_queue_.empty()) {
        incoming_queue_cond_.wait(lock);
    } else {
        incoming_queue_.Swap(&working_queue_);
    }
}

void ThreadBase::DoRun() {
    if (!is_initialized_)
        return;

    std::cout<<"DoRun enter"<<std::endl;
    while(is_running_) {
        if (working_queue_.empty()) {
            ReloadWorkingQueue();
        } else {
            Task task = std::move(working_queue_.front());
            working_queue_.pop();
            task.Run();
        }
    }
    std::cout<<"DoRun leave"<<std::endl;
}

}
}
