// Distributed under the MIT License that can be found in the LICENSE file.
// https://github.com/keunlas/kotools
//
// Author: Keunlas <keunlaz at gmail dot com>

#ifndef KOTOOLS_THREADPOOL_TASKQUEUE_H
#define KOTOOLS_THREADPOOL_TASKQUEUE_H

#include <atomic>
#include <memory>

#include "kotools/threadpool/task.h"

namespace kotools::threadpool {

/**
 * [TODO]
 *
 * Here are three features to expand
 *  1. batch
 *  2. bounded
 *  3. priority
 *
 */

class TaskQueue {
 public:
  using SizeType = std::size_t;

 public:
  TaskQueue();
  ~TaskQueue();

  void push(TaskPtr task);
  TaskPtr pop();  // If queue empty then pop a nullptr

  // In highly concurrent environments,
  // the value returned by size() may not be precise,
  // but this is a common feature of lock-free queues.
  inline SizeType size() { return size_.load(); }

 private:
  struct TaskNode;
  std::atomic<TaskNode*> head_;  // dummy
  std::atomic<TaskNode*> tail_;
  std::atomic_size_t size_{0};
};

}  // namespace kotools::threadpool

#endif  // !KOTOOLS_THREADPOOL_TASKQUEUE_H
