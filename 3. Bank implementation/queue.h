#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int Qdata_type;

struct Queue;

struct Queue* createQueue(int capacity);
//this function creates a queue
void destroyQueue(struct Queue *q);
//this function destroys the queue

int isEmpty(struct Queue *q);
//this function checks if the queue is empty, if it is, it returns 1, else it returns 0
int isFull(struct Queue *q);
//this function checks if the queue is  full, if it is, it returns 1, else it returns 0

int enqueue(struct Queue *q, int value);
//this function adds an element into the back of the queue
Qdata_type dequeue(struct Queue *q);
//this function removes the first element of the queue, if the queue is empty, it prints out a message and returns 0
//before using this function, check if the queue is empty, else you might get 0 without knowing if it's an element or indication that the queue is empty
Qdata_type firstItem(struct Queue *q);
//this function shows the first element of the queue without removing it, if the queue is empty, it prints out a message and returns 0
//before using this function, check if the queue is empty, else you might get 0 without knowing if it's an element or indication that the queue is empty
int queue_size(struct Queue *q);

#endif // QUEUE_H_INCLUDED
