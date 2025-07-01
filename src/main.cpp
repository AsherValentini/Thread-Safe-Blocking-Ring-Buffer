#include <iostream>
#include <thread>
#include "ring_buffer.hpp"
#include "tick.hpp"

// producer thread
void producer(std::shared_ptr<RingBuffer<Tick>>& buffer) {
  auto p1 = std::make_shared<Tick>("AAPL", 10.01);
  auto p2 = std::make_shared<Tick>("TSLA", 11.01);
  auto p3 = std::make_shared<Tick>("SMP", 12.01);
  auto p4 = std::make_shared<Tick>("WS30", 13.01);
  buffer->push(std::move(p1));
  buffer->push(std::move(p2));
  buffer->push(std::move(p3));
  buffer->push(std::move(p4));
}

// consumer thread
void consumer(std::shared_ptr<RingBuffer<Tick>>& buffer) { auto p1 = buffer->pop(); }

int main() {
  auto buffer = std::make_shared<RingBuffer<Tick>>();

  std::thread prod([&]() {
    producer(buffer);
    buffer->shutDown();
  });
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  std::thread cons([&]() { consumer(buffer); });

  cons.join();
  prod.join();

  return 0;
}

