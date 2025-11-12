// Distributed under the MIT License that can be found in the LICENSE file.
// https://github.com/keunlas/kotools
//
// Author: Keunlas <keunlaz at gmail dot com>

#include "kotools/threadpool/taskqueue.h"

#include "kotools/threadpool/task.h"

namespace kotools::threadpool {

TaskQueue::TaskQueue() : is_bounded_(false) {}

TaskQueue::TaskQueue(std::size_t capacity)
    : capacity_(capacity), is_bounded_(true) {}

TaskQueue::~TaskQueue() {
  while (queue_.empty() == false) {
    queue_.pop();
  }
}

bool TaskQueue::push(TaskPtr task) {
  std::lock_guard<std::mutex> lock(queue_mtx_);
  if (capacity_ < queue_.size()) {
    return false;
  }
  queue_.push(task);
  return true;
}

TaskPtr TaskQueue::pop() {
  std::lock_guard<std::mutex> lock(queue_mtx_);
  if (queue_.empty()) {
    return nullptr;
  }
  TaskPtr task = queue_.front();
  queue_.pop();
  return task;
}

}  // namespace kotools::threadpool
