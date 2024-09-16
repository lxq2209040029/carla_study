// Copyright (c) 2017 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#pragma once  // 确保头文件只被包含一次，避免重复包含导致的问题

#include "carla/Debug.h"  // 包含自定义调试功能的头文件
#include "carla/NonCopyable.h"  // 包含定义 NonCopyable 类的头文件，避免类被复制

#include <thread>
#include <vector>

namespace carla {

  class ThreadGroup : private NonCopyable {
  public:

    ThreadGroup() = default;

    ~ThreadGroup() {
      JoinAll();
    }
    
    // 创建一个新线程并执行给定的可调用对象。
    // 模板参数 F 是一个可调用对象类型。

    template <typename F>
    void CreateThread(F &&functor) {
      _threads.emplace_back(std::forward<F>(functor));
    }

    template <typename F>
    void CreateThreads(size_t count, F functor) {
      _threads.reserve(_threads.size() + count);
      for (size_t i = 0u; i < count; ++i) {
        CreateThread(functor);
      }
    }

    void JoinAll() {
      for (auto &thread : _threads) {
        DEBUG_ASSERT_NE(thread.get_id(), std::this_thread::get_id());
        if (thread.joinable()) {
          thread.join();
        }
      }
      _threads.clear();
    }

  private:

    std::vector<std::thread> _threads;
  };

} 
