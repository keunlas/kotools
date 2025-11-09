// Distributed under the MIT License that can be found in the LICENSE file.
// https://github.com/keunlas/kotools
//
// Author: Keunlas <keunlaz at gmail dot com>

#include "kotools/threadpool/taskqueue.h"

#include "kotools/threadpool/task.h"

namespace kotools::threadpool {

struct TaskQueue::TaskNode {
  TaskPtr task_;
  std::atomic<TaskNode*> next_;

  TaskNode() : next_(nullptr) {}
  explicit TaskNode(TaskPtr task) : task_(task), next_(nullptr) {}
};

TaskQueue::TaskQueue() {
  TaskNode* dummy = new TaskNode();
  head_.store(dummy, std::memory_order_relaxed);
  tail_.store(dummy, std::memory_order_relaxed);
}

TaskQueue::~TaskQueue() {
  TaskNode* current = head_.load();
  while (current) {
    TaskNode* next = current->next_.load();
    delete current;
    current = next;
  }
}

void TaskQueue::push(TaskPtr task) {
  TaskNode* new_node = new TaskNode(task);

  while (true) {
    TaskNode* current_tail = tail_.load(std::memory_order_acquire);
    TaskNode* tail_next = current_tail->next_.load(std::memory_order_acquire);

    // Check current_tail is tail_.
    if (current_tail != tail_.load(std::memory_order_acquire)) {
      continue;
    }

    // Check tail_next is change.
    if (tail_next != nullptr) {
      tail_.compare_exchange_strong(current_tail, tail_next,
                                    std::memory_order_release,
                                    std::memory_order_relaxed);
      continue;
    }

    // Put new_node to tail's next.
    if (current_tail->next_.compare_exchange_weak(tail_next, new_node,
                                                  std::memory_order_release,
                                                  std::memory_order_relaxed)) {
      // Update new tail.
      tail_.compare_exchange_strong(current_tail, new_node,
                                    std::memory_order_release,
                                    std::memory_order_relaxed);

      // Update size_
      size_.fetch_add(1, std::memory_order_relaxed);

      return;
    }
  }
}

TaskPtr TaskQueue::pop() {
  while (true) {
    TaskNode* curr_dummy = head_.load(std::memory_order_acquire);
    TaskNode* curr_tail = tail_.load(std::memory_order_acquire);
    TaskNode* curr_head = curr_dummy->next_.load(std::memory_order_acquire);

    // Check curr_dummy is head_(dummy)
    if (curr_dummy != head_.load(std::memory_order_acquire)) {
      continue;
    }

    // Check queue is empty
    if (curr_dummy == curr_tail) {
      if (curr_head == nullptr) {
        return nullptr;  // this queue is empty and tail is not changed
      }
      // Update new tail while tail is changed
      tail_.compare_exchange_strong(curr_tail, curr_head,
                                    std::memory_order_release,
                                    std::memory_order_relaxed);
      continue;
    }

    auto curr_task = curr_head->task_;

    // Recheck curr_dummy is head_(dummy)
    // If curr_dummy is head_ then make curr_head new dummy.
    if (head_.compare_exchange_strong(curr_dummy, curr_head,
                                      std::memory_order_release,
                                      std::memory_order_relaxed)) {
      delete curr_dummy;  // delete old dummy.

      /**
       * [TODO]
       *
       * Because the node currently popped out becomes the new dummy,
       * the memory of the new dummy can be freed here for saving memory.
       * But my instinct tells me that this is thread-unsafe.
       *
       * // curr_head->task_.reset();
       *
       */

      // Update size_
      size_.fetch_sub(1, std::memory_order_relaxed);

      return curr_task;
    }
  }
}

}  // namespace kotools::threadpool
