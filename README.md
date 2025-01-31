LeetCode Style Question: Thread-Safe Queue and Singleton Implementation

Problem Description

Design and implement two classes: a ThreadSafeQueue and a Singleton.

1. ThreadSafeQueue

Implement a thread-safe queue that supports multiple producers and multiple consumers. The queue should allow the following operations:
	1.	Push (Enqueue):
	•	Add an element to the end of the queue.
	•	If there are consumers waiting for elements, notify them.
	2.	Pop (Dequeue):
	•	Remove and return the element at the front of the queue.
	•	If the queue is empty, block the calling thread until an element becomes available.

You should use a condition variable to manage synchronization between threads.

