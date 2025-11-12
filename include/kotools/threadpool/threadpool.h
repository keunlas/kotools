// Distributed under the MIT License that can be found in the LICENSE file.
// https://github.com/keunlas/kotools
//
// Author: Keunlas <keunlaz at gmail dot com>

#ifndef KOTOOLS_THREADPOOL_THREADPOOL_H
#define KOTOOLS_THREADPOOL_THREADPOOL_H

#include <cstddef>
#include <memory>
#include <thread>
#include <vector>

#include "kotools/threadpool/taskqueue.h"

namespace kotools::threadpool {

class Task;
class TaskQueue;

class ThreadPool {
 public:
  using TaskPtr = std::shared_ptr<Task>;
  using ThreadVector = std::vector<std::thread>;

 public:
  ThreadPool(std::size_t n_threads);
  ThreadPool(std::size_t n_queuesize, std::size_t n_threads);
  ~ThreadPool();

  void start();
  void quit();

  void add_task(TaskPtr task);

 private:
  TaskQueue queue_;
  std::size_t n_threads_;
  ThreadVector threads_{};
  std::atomic_bool exit_{false};
};

}  // namespace kotools::threadpool

#endif  // !KOTOOLS_THREADPOOL_THREADPOOL_H
