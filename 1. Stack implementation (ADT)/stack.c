#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void push(struct Stack *stack, int data)
{
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
}

void pop(struct Stack *stack)
{
    if (stack->top == NULL)
    {
        printf("Error: Stack is empty\n");
        return;
    }
    struct Node *temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
}

int top(struct Stack *stack)
{
    if (stack->top == NULL)
    {
        printf("Error: Stack is empty\n");
        return;
    }
    return stack->top->data;
}

int isEmpty(struct Stack *stack)
{
    return stack->top == NULL;
}

int size(struct Stack *stack)
{
    return stack->size;
}

void destroy(struct Stack *stack)
{
    while (stack->top != NULL)
    {
        pop(stack);
    }
}

void printStack(struct Stack *stack)
{
    struct Node *temp = stack->top;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    struct Stack stack;
    stack.top = NULL;
    stack.size = 0;

    int choice;
    int data;

    while (1)
    {
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Top\n");
        printf("4. Size\n");
        printf("5. Is Empty\n");
        printf("6. Print Stack\n"); // add new option to print stack
        printf("7. Destroy\n");
        printf("8. Quit\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number.\n");
            while(getchar() != '\n'); // clear input buffer
            continue;
        }

        switch (choice)
        {
        case 1:
            printf("Enter the data to be pushed: ");
            scanf("%d", &data);
            push(&stack, data);
            break;
        case 2:
            pop(&stack);
            break;
        case 3:
            data = top(&stack);
            if (data != -1)
            {
                printf("Top element: %d\n", data);
            }
            break;
        case 4:
            printf("Size: %d\n", size(&stack));
            break;
        case 5:
            if (isEmpty(&stack))
            {
                printf("Stack is empty\n");
            }
            else
            {
                printf("Stack is not empty\n");
            }
            break;
        case 6:
            printStack(&stack); // call printStack function
            break;
        case 7:
            destroy(&stack);
            printf("Stack has been destroyed\n");
            break;
        case 8:
            exit(0);
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    }
    return 0;
}
