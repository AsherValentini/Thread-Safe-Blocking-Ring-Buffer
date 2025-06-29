Ring Buffer, But Thread-Safe

Difficulty: Medium-Hard (≈1 hr)
Theme: Real-time data ingestion
Focus: Thread safety, condition variables, bounded buffers
Module Brief:

You're going to implement a bounded thread-safe ring buffer — aka circular queue — suitable for high-throughput, low-latency environments like real-time data ingestion pipelines.
Core Requirements:

    Fixed-size buffer (N)

    push(T&& item) — waits if buffer is full

    pop() — waits if buffer is empty

    shutdown() — gracefully unblocks waiting threads

    Use std::mutex and std::condition_variable for locking and signaling

    Support multiple producers and multiple consumers

Tomorrow’s Focus:

    You’ll write Google Tests that stress the buffer from multiple threads

    Validate ordering, blocking behavior, and graceful shutdown

Suggested File Layout

/include
  ring_buffer.hpp     <-- your main module
/tests
  test_ring_buffer.cpp <-- for tomorrow
/src
  main.cpp            <-- optional manual driver

Why This Challenge Matters:

This is a classic building block in trading systems, telemetry processors, and sensor pipelines. If you can write a solid, lock-safe ring buffer with shutdown support — that’s serious engineering muscle.


