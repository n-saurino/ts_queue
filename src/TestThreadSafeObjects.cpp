#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include "ThreadSafeQueue.hpp" // Adjust the include path as necessary
#include <atomic> 

class ThreadSafeQueueTest : public ::testing::Test {
protected:
    ThreadSafeQueue<int> queue;
};

TEST_F(ThreadSafeQueueTest, PushPopSingleThread) {
    EXPECT_EQ(queue.Push(1), true);
    EXPECT_EQ(queue.Push(2), true);
    EXPECT_EQ(queue.Push(3), true);

    EXPECT_EQ(queue.Pop().value(), 1);
    EXPECT_EQ(queue.Pop().value(), 2);
    EXPECT_EQ(queue.Pop().value(), 3);

    EXPECT_EQ(queue.Empty(), true); // Queue is empty
}

TEST_F(ThreadSafeQueueTest, SizeFunctionality) {
    EXPECT_EQ(queue.Size(), 0);
    queue.Push(10);
    queue.Push(20);
    EXPECT_EQ(queue.Size(), 2);
    queue.Pop();
    EXPECT_EQ(queue.Size(), 1);
    queue.Pop();
    EXPECT_EQ(queue.Size(), 0);
}

TEST_F(ThreadSafeQueueTest, StopBehavior) {
    std::thread producer([&]() {
        for (int i = 0; i < 5; ++i) {
            queue.Push(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        queue.Stop();
    });

    std::thread consumer([&]() {
        while (true) {
            auto value = queue.Pop();
            if (!value.has_value()) break; // Queue stopped
            std::cout << "Consumed: " << value.value() << std::endl;
        }
    });

    producer.join();
    consumer.join();

    EXPECT_EQ(queue.Pop().has_value(), false); // Queue stopped and empty
}

TEST_F(ThreadSafeQueueTest, PopBlocksWhenEmpty) {
    bool pop_completed = false;

    std::thread consumer([&]() {
        auto value = queue.Pop();
        if (value.has_value()) {
            pop_completed = true;
        }
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    EXPECT_EQ(pop_completed, false); // Pop should be waiting

    queue.Push(42); // Unblock the consumer
    consumer.join();

    EXPECT_EQ(pop_completed, true);
    EXPECT_EQ(queue.Size(), 0);
}

TEST_F(ThreadSafeQueueTest, MultiProducerMultiConsumer) {
    const int num_producers = 3;
    const int num_consumers = 3;
    const int items_per_producer = 10;

    std::atomic<int> total_consumed{0};

    // Producer threads
    std::vector<std::thread> producers;
    for (int i = 0; i < num_producers; ++i) {
        producers.emplace_back([&, i]() {
            for (int j = 0; j < items_per_producer; ++j) {
                queue.Push(i * 100 + j);
            }
        });
    }

    // Consumer threads
    std::vector<std::thread> consumers;
    for (int i = 0; i < num_consumers; ++i) {
        consumers.emplace_back([&]() {
            while (true) {
                auto value = queue.Pop();
                if (!value.has_value()) break;
                total_consumed.fetch_add(1);
            }
        });
    }

    // Wait for producers to finish
    for (auto& producer : producers) {
        producer.join();
    }

    // Stop the queue and wait for consumers
    queue.Stop();
    for (auto& consumer : consumers) {
        consumer.join();
    }

    EXPECT_EQ(total_consumed, num_producers * items_per_producer);
}

TEST_F(ThreadSafeQueueTest, StopUnblocksPop) {
    bool pop_completed = false;

    std::thread consumer([&]() {
        auto value = queue.Pop();
        if (!value.has_value()) {
            pop_completed = true; // Pop was unblocked by stop
        }
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    EXPECT_EQ(pop_completed, false); // Pop should be waiting

    queue.Stop(); // Unblock the consumer
    consumer.join();

    EXPECT_EQ(pop_completed, true);
}