#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// Stack structure
typedef struct {
    int arr[MAX];
    int top;
} Stack;

// Queue structure with two stacks
typedef struct {
    Stack s1, s2;
} Queue;

// Stack operations
void push(Stack *s, int val) { s->arr[++s->top] = val; }
int pop(Stack *s) { return s->arr[s->top--]; }
int isEmpty(Stack *s) { return s->top==-1; }

// Method 1: Push costly
void enqueue_m1(Queue *q, int val) {
    while (!isEmpty(&q->s1)) push(&q->s2, pop(&q->s1));
    push(&q->s1, val);
    while (!isEmpty(&q->s2)) push(&q->s1, pop(&q->s2));
}

int dequeue_m1(Queue *q) { return pop(&q->s1); }// dequeue cheap
void enqueue_m2(Queue *q, int val) { push(&q->s1, val); }// enqueue cheap

// Method 2: Pop costly
int dequeue_m2(Queue *q) {
    if (isEmpty(&q->s2)) {
        while (!isEmpty(&q->s1)) push(&q->s2, pop(&q->s1));
    }
    return pop(&q->s2);
}

// Display queue
void display(Queue *q, int method) {
    if (method == 1) {
        for (int i = 0; i <= q->s1.top; i++) printf("%d ", q->s1.arr[i]);
    } else {
        if (isEmpty(&q->s2)) {
            for (int i = 0; i <= q->s1.top; i++) printf("%d ", q->s1.arr[i]);
        } else {
            for (int i = q->s2.top; i >= 0; i--) printf("%d ", q->s2.arr[i]);
            for (int i = 0; i <= q->s1.top; i++) printf("%d ", q->s1.arr[i]);
        }
    }
    printf("\n");
}

int main() {
    Queue q1 = {{-1}, {-1}}, q2 = {{-1}, {-1}};
    int choice, val, method;
    
    printf("Choose Method (1-Push costly, 2-Pop costly): ");
    scanf("%d", &method);
    
    while (1) {
        printf("\n1.Enqueue 2.Dequeue 3.Display 4.Exit\nChoice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: printf("Enter value: "); scanf("%d", &val);
                    method == 1 ? enqueue_m1(&q1, val) : enqueue_m2(&q2, val);
                    break;
            case 2: printf("Dequeued: %d\n", method == 1 ? dequeue_m1(&q1) : dequeue_m2(&q2));
                    break;
            case 3: method == 1 ? display(&q1, 1) : display(&q2, 2);
                    break;
            case 4: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}