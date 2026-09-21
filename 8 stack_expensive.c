#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int arr[MAX];
    int front, rear;
} Queue;

void init(Queue *q) { q->front = q->rear = -1; }

int isEmpty(Queue *q) { return q->front == -1; }

void enqueue(Queue *q, int val) {
    if (isEmpty(q)) 
        q->front = 0;
    q->rear = (q->rear + 1) % MAX;
    q->arr[q->rear] = val;
}

int dequeue(Queue *q) {
    int val = q->arr[q->front];
    if (q->front == q->rear) 
        q->front = q->rear = -1;
    else 
        q->front = (q->front + 1) % MAX;
    return val;
}

// Method 1: Push costly
void push_m1(Queue *q1, Queue *q2, int val) {
    while (!isEmpty(q1)) 
        enqueue(q2, dequeue(q1));
    enqueue(q1, val);
    while (!isEmpty(q2)) 
        enqueue(q1, dequeue(q2));
}

int pop_m1(Queue *q1) { return dequeue(q1); }

// Method 2: Pop costly
void push_m2(Queue *q1, int val) { enqueue(q1, val); }

int pop_m2(Queue *q1, Queue *q2){
    while(q1->front != q1->rear) 
        enqueue(q2, dequeue(q1));
    int val=dequeue(q1);
    while (!isEmpty(q2)) 
        enqueue(q1, dequeue(q2));
    return val;
}

void display(Queue *q) {
    if (isEmpty(q)) 
    { 
        printf("Empty!\n"); 
        return; 
    }

    int i=q->front;
    while (1){
        printf("%d ",q->arr[i]);
        if (i==q->rear) break;
        i=(i+1)%MAX;
    }
    printf("\n");
}

int main() {
    Queue q1, q2;
    init(&q1);
    init(&q2);
    int choice, val, method;
    
    printf("Choose Method (1-Push costly, 2-Pop costly): ");
    scanf("%d", &method);
    
    while (1) {
        printf("\n1.Push 2.Pop 3.Display 4.Exit\nChoice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: 
                printf("Enter value: "); 
                scanf("%d", &val);
                if(method == 1) 
                    push_m1(&q1, &q2, val);
                else 
                    push_m2(&q1, val);
                break;
                
            case 2: 
                if(method == 1) 
                    printf("Popped: %d\n", pop_m1(&q1));
                else 
                    printf("Popped: %d\n", pop_m2(&q1, &q2));
                break;
                
            case 3: 
                display(&q1);
                break;
                
            case 4: 
                exit(0);
                
            default: 
                printf("Invalid choice!\n");
        }
    }
    return 0;
}