#include "kotools/threadpool/taskqueue.h"

#include <cstdio>
#include <thread>
#include <vector>

#include "kotools/threadpool/task.h"

using namespace kotools::threadpool;

TaskQueue queue;

class IntTask : public Task {
 public:
  IntTask(int num) : num_(num) {}
  void process() override {}

 private:
  int num_;
};

void producer(int id, int cnt) {
  for (int i = 0; i < cnt; ++i) {
    queue.push(std::make_shared<IntTask>(id * 1000 + i));
  }
}

void consumer(int cnt) {
  for (int i = 0; i < cnt; ++i) {
    if (auto item = queue.pop()) {
      item->process();
    }
  }
}

void test(int n_producers, int n_produce, int n_comsumers, int n_comsume) {
  std::vector<std::thread> producers;
  std::vector<std::thread> consumers;

  for (int i = 0; i < n_producers; ++i) {
    producers.emplace_back(producer, i, n_produce);
  }

  for (int i = 0; i < n_comsumers; ++i) {
    consumers.emplace_back(consumer, n_comsume);
  }

  for (auto& t : producers) t.join();
  for (auto& t : consumers) t.join();
}

int main() {
  test(4, 1000, 2, 2000);  // produce equal comsume
  test(4, 1000, 2, 1500);  // more produce
  test(4, 1000, 2, 3000);  // more comsume
  return 0;
}
