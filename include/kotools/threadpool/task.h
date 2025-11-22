// Distributed under the MIT License that can be found in the LICENSE file.
// https://github.com/keunlas/kotools
//
// Author: Keunlas <keunlaz at gmail dot com>

#ifndef KOTOOLS_THREADPOOL_TASK_H
#define KOTOOLS_THREADPOOL_TASK_H

#include <memory>

namespace kotools::threadpool {

class Task {
 public:
  virtual ~Task() {}
  virtual void process() = 0;
};

using TaskPtr = std::shared_ptr<Task>;

}  // namespace kotools::threadpool

#endif  // !KOTOOLS_THREADPOOL_TASK_H
