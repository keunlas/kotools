// Distributed under the MIT License that can be found in the LICENSE file.
// https://github.com/keunlas/kotools
//
// Author: Keunlas <keunlaz at gmail dot com>

#include "kotools/threadpool/threadpool.h"

#include "kotools/threadpool/task.h"
#include "kotools/threadpool/taskqueue.h"

namespace kotools::threadpool {

ThreadPool::ThreadPool(std::size_t n_threads)
    : queue_(), n_threads_(n_threads) {}

ThreadPool::ThreadPool(std::size_t n_queuesize, std::size_t n_threads)
    : queue_(n_queuesize), n_threads_(n_threads) {}

ThreadPool::~ThreadPool() {
  for (auto&& t : threads_) {
    if (t.joinable()) {
      t.join();
    }
  }
}

void ThreadPool::start() {
  for (std::size_t i = 0; i < n_threads_; ++i) {
    threads_.emplace_back([this]() {
      while (exit_.load() == false) {
        auto curr_task = queue_.pop();
        if (curr_task) {
          (*curr_task).process();
        } else {
          std::this_thread::yield();
        }
      }
    });
  }
}

void ThreadPool::quit() { exit_.store(true); }

void ThreadPool::add_task(TaskPtr task) {
  if (exit_.load() == true) {
    return;
  }

  while (queue_.push(task) == false) {
    if (exit_.load() == true) {
      return;
    }
    std::this_thread::yield();
  }
}

}  // namespace kotools::threadpool
