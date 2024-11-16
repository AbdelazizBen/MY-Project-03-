#include <stdio.h>
#include <stdlib.h>

#define MAX 5  


typedef struct {
    int arr[MAX];
    int front;
    int rear;
} Queue;



void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return (q->front == -1);
}


int isFull(Queue *q) {
    return (q->rear == MAX - 1);
}

void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->arr[q->rear] = value;
}


int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int value = q->arr[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return value;
}


int peek(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->arr[q->front];
}



typedef struct {
    int arr[MAX];
    int front;
    int rear;
} CircularQueue;


void initCircularQueue(CircularQueue *q) {
    q->front = -1;
    q->rear = -1;
}


int isCircularQueueEmpty(CircularQueue *q) {
    return (q->front == -1);
}


int isCircularQueueFull(CircularQueue *q) {
    return ((q->rear + 1) % MAX == q->front);
}


void enqueueCircularQueue(CircularQueue *q, int value) {
    if (isCircularQueueFull(q)) {
        printf("Circular Queue is full\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX;
    q->arr[q->rear] = value;
}


int dequeueCircularQueue(CircularQueue *q) {
    if (isCircularQueueEmpty(q)) {
        printf("Circular Queue is empty\n");
        return -1;
    }
    int value = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
    return value;
}


int peekCircularQueue(CircularQueue *q) {
    if (isCircularQueueEmpty(q)) {
        printf("Circular Queue is empty\n");
        return -1;
    }
    return q->arr[q->front];
}



typedef struct {
    int* arr;
    int top;
} Stack;

// Stack Operations
void initStack(Stack *s) {
    s->arr = (int*)malloc(MAX * sizeof(int));
    s->top = -1;
}

void push(Stack *s, int value) {
    s->arr[++s->top] = value;
}

int pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->arr[s->top--];
}

int isStackEmpty(Stack *s) {
    return s->top == -1;
}


void reverseQueueUsingStacks(Queue *q) {
    Stack s1, s2;
    initStack(&s1);
    initStack(&s2);


    while (!isEmpty(q)) {
        push(&s1, dequeue(q));
    }

   
    while (!isStackEmpty(&s1)) {
        push(&s2, pop(&s1));
    }

 
    while (!isStackEmpty(&s2)) {
        enqueue(q, pop(&s2));
    }
}


void enqueueStackQueue(Stack *stack1, int value) {
    push(stack1, value);
}

int dequeueStackQueue(Stack *stack1, Stack *stack2) {
    if (isStackEmpty(stack2)) {
        while (!isStackEmpty(stack1)) {
            push(stack2, pop(stack1));
        }
    }
    return pop(stack2);
}



#define MAX_CHAR 256

void firstNonRepeatingCharStream(char *stream) {
    int freq[MAX_CHAR] = {0};
    Queue q;
    initQueue(&q);

    for (int i = 0; stream[i] != '\0'; i++) {
        char ch = stream[i];

        enqueue(&q, ch);
        freq[ch]++;

        while (!isEmpty(&q) && freq[q.arr[q.front]] > 1) {
            dequeue(&q);
        }

       
        if (!isEmpty(&q)) {
            printf("First non-repeating character: %c\n", q.arr[q.front]);
        } else {
            printf("No non-repeating character\n");
        }
    }
}


int main() {
   
    Queue q;
    initQueue(&q);
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    printf("Dequeue from basic queue: %d\n", dequeue(&q));

    CircularQueue cq;
    initCircularQueue(&cq);
    enqueueCircularQueue(&cq, 10);
    enqueueCircularQueue(&cq, 20);
    printf("Dequeue from circular queue: %d\n", dequeueCircularQueue(&cq));

    Queue reverseQueue;
    initQueue(&reverseQueue);
    enqueue(&reverseQueue, 1);
    enqueue(&reverseQueue, 2);
    enqueue(&reverseQueue, 3);
    reverseQueueUsingStacks(&reverseQueue);
    printf("Reversed queue after using two stacks:\n");
    while (!isEmpty(&reverseQueue)) {
        printf("%d ", dequeue(&reverseQueue));
    }
    printf("\n");

    Stack stack1, stack2;
    initStack(&stack1);
    initStack(&stack2);
    enqueueStackQueue(&stack1, 10);
    enqueueStackQueue(&stack1, 20);
    printf("Dequeue from simulated queue: %d\n", dequeueStackQueue(&stack1, &stack2));

  
    char stream[] = "geeksforgeeks";
    printf("First non-repeating characters in stream:\n");
    firstNonRepeatingCharStream(stream);

    return 0;
}
