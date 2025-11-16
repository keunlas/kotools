#include "kotools/threadpool/threadpool.h"

#include <cstdio>
#include <thread>
#include <vector>

#include "kotools/threadpool/task.h"
#include "kotools/threadpool/taskqueue.h"

using namespace kotools::threadpool;

class IntTask : public Task {
 public:
  IntTask(int num) : num_(num) {}
  void process() override { std::printf("Num: %d\n", num_); }

 private:
  int num_;
};

int main() {
  ThreadPool pool(8192, 2);
  pool.start();

  std::thread t{[&pool]() {
    // for (int i = 0; i < 10000; ++i) {
    for (int i = 0; true; ++i) {
      // std::this_thread::sleep_for(std::chrono::microseconds(100));
      pool.add_task(std::make_shared<IntTask>(i));
    }
  }};

  t.join();
  pool.quit();
  return 0;
}
