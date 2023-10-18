#include <stdlib.h>
#include "queue.h"

 struct Node {
	int value;
	struct Node *next;
};

struct Queue {
	int size;
	int max_size;
	struct Node *head;
	struct Node *tail;
};

struct Queue* createQueue(int capacity)
{
	struct Queue *q;
	q = malloc(sizeof(struct Queue));

	if (q == NULL) {
		return q;
	}

	q->size = 0;
	q->max_size = capacity;
	q->head = NULL;
	q->tail = NULL;

	return q;
}

void destroyQueue(struct Queue *q)
{
	while (q->head != NULL) {

		struct Node *tmp = q->head;
		free(q->head);
		q->head = q->head->next;

		free(tmp);
	}

	if (q->tail != NULL) {
		free(q->tail);
	}

	free (q);
}

int isEmpty(struct Queue *q)
{
    if(q->tail == NULL)
        return 1;
    else
        return 0;
}

int isFull(struct Queue *q)
{
    if (malloc(sizeof(q)) == NULL)
        return 1;
    else
        return 0;
}

int enqueue(struct Queue *q, int value)//void value
{
	if ((q->size + 1) > q->max_size) {
		return q->size;
	}

	struct Node *node = malloc(sizeof(struct Node));

	if (node == NULL) {
		return q->size;
	}

	node->value = value;
	node->next = NULL;

	if (q->head == NULL) {
		q->head = node;
		q->tail = node;
		q->size = 1;

		return q->size;
	}


	q->tail->next = node;
	q->tail = node;
	q->size += 1;

	return q->size;
}

Qdata_type dequeue(struct Queue *q)
{
	if (q->size == 0) {
		return 0;
	}
	int a;
	struct Node *tmp = NULL;

	a = q->head->value;
	tmp = q->head;
	q->head = q->head->next;
	q->size -= 1;

	free(tmp);

	return a;
}

Qdata_type firstItem(struct Queue *q)
{
    if(isEmpty(q) == 1)
    {
        return 0;
    }
    else
    {
        return (q->head->value);
    }
}

int queue_size(struct Queue *q) {
	return q->size;
}
