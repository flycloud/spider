#include <spider/core/include/task.hpp>

namespace spider {
namespace core {

Task::Task(std::function<void()> func) {
    func_ = std::move(func);
    is_cancelled_ = false;
    is_completed_ = false;
}

void Task::Cancel() {
    is_cancelled_ = true;
}

void Task::Run() {
    if (is_completed_ || is_cancelled_)
        return;

    if (func_) {
        func_();
    }
    is_completed_ = true;
}

void TaskQueue::Swap(TaskQueue* dest_queue) {
    c.swap(dest_queue->c);
}

}
}
