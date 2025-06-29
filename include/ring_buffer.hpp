#pragma once

#include <optional>
#include <memory>
#include <stddef.h>
#include <array>
#include <condition_variable>
#include <mutex>

template <typename T, std::size_t Capacity = 1024>
class RingBuffer {
public:
  RingBuffer() : head_(0), tail_(0) {}
  void push() {
    // thread management
    std::unique_lock<std::mutex> myLock(mtx_);
    prodCV_.wait(myLock, [this]() {
      return
    });
  }

  std::optional<std::shared_ptr<T>> pop() { return std::nullopt; }

private:
  void increment(std::size_t& index) {
    // wrap around incrementer
    index = (index + 1) % Capacity;
  }
  std::array<std::shared_ptr<T>, Capacity> buffer_;
  std::size_t head_;
  std::size_t tail_;

  std::mutex mtx_;
  std::condition_variable prodCV_;
  std::condition_variable consCV_;
};