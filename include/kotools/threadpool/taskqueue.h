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
  TaskQueue();
  ~TaskQueue();

  void push(TaskPtr task);
  TaskPtr pop();  // If queue empty then pop a nullptr

 private:
  struct TaskNode;
  std::atomic<TaskNode*> head_;  // dummy
  std::atomic<TaskNode*> tail_;
};

}  // namespace kotools::threadpool

#endif  // !KOTOOLS_THREADPOOL_TASKQUEUE_H
