#include <gtest/gtest.h>
#include "ring_buffer.hpp"
#include "tick.hpp"

TEST(Dummy, SetupChecker) { ASSERT_EQ(1, 1); }

TEST(Tick, PushPop) {

  auto buffer = std::make_shared<RingBuffer<Tick>>();

  auto p1 = std::make_shared<Tick>("AAPL", 10.01);

  buffer->push(p1);

  auto p2 = buffer->pop();

  ASSERT_EQ(p1, p2);
}

