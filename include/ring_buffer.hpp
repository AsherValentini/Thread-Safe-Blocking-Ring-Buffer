#pragma once

#include <optional>
#include <memory>
#include <stddef.h>
#include <array>
#include <condition_variable>
#include <mutex>
#include <iostream>

template <typename T, std::size_t Capacity = 4>
class RingBuffer {
public:
  RingBuffer() : head_(0), tail_(0), shutDown_(false) {}
  void push(std::shared_ptr<T> sharedPtr) {

    std::unique_lock<std::mutex> myLock(mtx_);
    std::size_t next = increment(head_);
    prodCV_.wait(myLock, [&]() { return next != tail_ || shutDown_; });

    if (shutDown_) {
      std::cout << "[RingBuffer] shutdown" << std::endl;
      return;
    }
    std::cout << "[RingBuffer] pushed tick: " << *sharedPtr << std::endl;

    buffer_[head_] = std::move(sharedPtr);
    head_ = next;

    consCV_.notify_all();
  }

  std::shared_ptr<T> pop() {
    std::unique_lock<std::mutex> myLock(mtx_);
    consCV_.wait(myLock, [this]() { return head_ != tail_; });

    auto ptr = std::move(buffer_[tail_]);
    tail_ = increment(tail_);

    prodCV_.notify_all();

    std::cout << "[RingBuffer] popped tick: " << *ptr << std::endl;

    return ptr;
  }

  void shutDown() {
    {
      std::unique_lock<std::mutex> myLock(mtx_);
      shutDown_ = true;
    }
    prodCV_.notify_all();
  }

private:
  std::size_t increment(std::size_t index) {
    // wrap around incrementer
    return (index + 1) % Capacity;
  }
  std::array<std::shared_ptr<T>, Capacity> buffer_;
  std::size_t head_;
  std::size_t tail_;

  std::mutex mtx_;
  std::condition_variable prodCV_;
  std::condition_variable consCV_;

  bool shutDown_;
};