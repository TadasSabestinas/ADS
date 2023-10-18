#ifndef STACK_H
#define STACK_H

struct Node
{
    int data;
    struct Node *next;
};

struct Stack
{
    struct Node *top;
    int size;
};

void push(struct Stack *stack, int data);
void pop(struct Stack *stack);
int top(struct Stack *stack);
int isEmpty(struct Stack *stack);
int size(struct Stack *stack);
void destroy(struct Stack *stack);
void printStack(struct Stack *stack);

#endif
