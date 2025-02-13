# Implement a Thread-safe Queue

## Problem Description

Design and implement two fundamental thread-safe classes commonly used in concurrent programming: a `ThreadSafeQueue` and a `Singleton`. The implementation must ensure thread safety while maintaining efficient performance characteristics.

## Part 1: Thread-Safe Queue

Design a queue that safely handles multiple producers and multiple consumers with proper synchronization.

### Core Requirements

#### 1. Push Operation (Enqueue)
- Add element to end of queue
- Notify waiting consumers
- Thread-safe implementation

#### 2. Pop Operation (Dequeue)
- Remove and return front element
- Block if queue is empty
- Resume when elements become available

### Interface

```cpp
template<typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue();
    
    // Add element to queue
    void push(const T& value);
    
    // Remove and return element from queue
    // Blocks if queue is empty
    T pop();
    
    // Check if queue is empty
    bool empty() const;
    
    // Get current size of queue
    size_t size() const;
};
```

### Technical Requirements

#### Thread Safety
1. Safe concurrent access from multiple threads
2. Protection against race conditions
3. Proper synchronization mechanisms

#### Synchronization
1. Use of condition variables for thread coordination
2. Efficient waiting mechanism for empty queue
3. Proper notification system for new elements

#### Performance Considerations
1. Minimize lock contention
2. Efficient resource usage
3. Optimal wake-up mechanism for waiting threads

## Best Practices

1. Use RAII for resource management
2. Implement proper exception handling
3. Consider memory ordering requirements
4. Use appropriate synchronization primitives
5. Document thread safety guarantees

## Performance Considerations

### Metrics to Monitor
1. Queue operation latency
2. Thread contention rates
3. Memory usage patterns
4. Cache performance
5. Context switching overhead

### Optimization Strategies
1. Lock granularity adjustment
2. Memory allocation optimization
3. Cache-friendly data structure layout
4. Efficient notification mechanisms

## Testing Considerations

### Test Scenarios
1. Single producer, single consumer
2. Multiple producers, single consumer
3. Single producer, multiple consumers
4. Multiple producers, multiple consumers
5. Empty queue scenarios
6. Full queue scenarios

### Validation Points
1. Thread safety verification
2. Order preservation
3. Memory leak detection
4. Deadlock prevention
5. Performance under load

## Common Pitfalls to Avoid

1. Race conditions during push/pop operations
2. Improper condition variable usage
3. Unnecessary thread wake-ups
4. Memory leaks in cleanup
5. Incorrect synchronization patterns
