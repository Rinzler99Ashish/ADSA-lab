#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int *arr;
    int front;
    int rear;
    int count;
    int size;
} CircularQueueArray;

bool is_empty(CircularQueueArray *q) {
    return q->count==0;
}

bool is_full(CircularQueueArray *q) {
    return q->count==q->size;
}

void enqueue(CircularQueueArray *q) {
    if (is_full(q)){
        printf("Queue is full\n");
        return;
    }

    int val;
    printf("Enter data to be enqueued: ");
    scanf("%d", &val);

    q->rear=(q->rear+1)%q->size;
    q->arr[q->rear] = val;
    q->count++;

    printf("Enqueued %d\n", val);
}

void dequeue(CircularQueueArray *q) {
    if (is_empty(q)){
        printf("Queue is already empty\n");
        return;
    }

    int val=q->arr[q->front];
    printf("Dequeued value is %d\n", val);

    q->front=(q->front+1)%q->size;
    q->count--;
}

void print_Queue(CircularQueueArray *q){
    if (is_empty(q)){
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements are: ");

    int i=q->front;
    for(int j=0; j<q->count; j++) {
        printf("%d ",q->arr[i]);
        i=(i+1)%q->size;
    }

    printf("\n");
}

int main(){
    CircularQueueArray q;
    printf("Enter queue size: ");
    scanf("%d", &q.size);

    q.arr=(int *)malloc(q.size*sizeof(int));

    q.front=0;
    q.rear=-1;
    q.count=0;


    while(1) {
        printf("\nEnter 1 to Enqueue\n");
        printf("Enter 2 to Dequeue\n");
        printf("Enter 3 to Display elements\n");
        printf("Enter 4 to Exit\n");

        int n;
        scanf("%d", &n);

        if(n==1)
            enqueue(&q);
        else if(n==2)
            dequeue(&q);
        else if(n==3)
            print_Queue(&q);
        else{
            printf("Exit\n");
            return 0;
        }
    }
    return 0;
}