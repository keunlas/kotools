// Distributed under the MIT License that can be found in the LICENSE file.
// https://github.com/keunlas/kotools
//
// Author: Keunlas <keunlaz at gmail dot com>

#ifndef KOTOOLS_THREADPOOL_TASKQUEUE_H
#define KOTOOLS_THREADPOOL_TASKQUEUE_H

#include <atomic>
#include <memory>
#include <mutex>
#include <queue>

#include "kotools/threadpool/task.h"

namespace kotools::threadpool {

/**
 * [TODO]
 *
 * Here are three features to expand
 *  1. batch
 *  2. priority
 *
 */

class TaskQueue {
 public:
  using TaskPtr = std::shared_ptr<Task>;

 public:
  TaskQueue();                      // unbounded queue
  TaskQueue(std::size_t capacity);  // bounded queue
  ~TaskQueue();

  // Return true if push successfully
  bool push(TaskPtr task);

  // Return nullptr if queue empty
  TaskPtr pop();

 private:
  std::mutex queue_mtx_{};
  std::queue<TaskPtr> queue_{};
  std::size_t capacity_;
  bool is_bounded_;
};

}  // namespace kotools::threadpool

#endif  // !KOTOOLS_THREADPOOL_TASKQUEUE_H
