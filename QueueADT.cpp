#include "QueueADT.hpp"


template <class Q>
void Queue<Q>::enqueue(Q val){
	QueueNode* newNode; // Pointer to a new node

	// Allocate a new node and store num there.
	newNode = new QueueNode;
	if (!newNode)
		return;
	newNode->value = val;
	newNode->next = nullptr;

// Update links and counter
	if (!front) // front is NULL: empty queue
		front = newNode;
	else
		rear->next = newNode;

	rear = newNode;
	length++;
}

template <class Q>
Q Queue<Q>::dequeue() {
	Q retVal = nullptr;
	QueueNode* s = nullptr;
	if (front) {
		retVal = front->value;
		s = front->next;
		delete front;
		front = s;
	}
	return retVal;
}