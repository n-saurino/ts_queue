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

2. Singleton

Implement a Singleton class that:
	1.	Ensures only one instance of the class exists throughout the program.
	2.	Is thread-safe when accessed in a multi-threaded environment.

Class Definitions
	1.	ThreadSafeQueue Class
	•	ThreadSafeQueue():
	•	Initializes the queue.
	•	void push(int value):
	•	Adds a value to the queue.
	•	int pop():
	•	Removes and returns the value at the front of the queue. Blocks if the queue is empty.
	•	Constraints:
	•	The queue must support concurrent access by multiple producers and consumers.
	2.	Singleton Class
	•	static Singleton* getInstance():
	•	Returns the single instance of the Singleton class.
	•	Constraints:
	•	The getInstance method must be thread-safe and ensure only one instance exists.

Example

Input:
	•	A ThreadSafeQueue with multiple threads pushing and popping values.
	•	A Singleton instance is accessed from multiple threads.

Output:

ThreadSafeQueue operations:
push(10)
push(20)
pop() => 10
pop() => 20

Singleton operations:
Singleton instance accessed from multiple threads: Address = 0x7ffeea112af0

Follow-Up
	1.	How would you modify the ThreadSafeQueue to add a timeout to the pop operation?
	2.	How can you ensure the Singleton instance is lazily initialized?