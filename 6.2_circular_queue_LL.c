#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;
 
typedef struct {
    Node *rear;   // points to the last node; rear->next is the front
    int count;
} CircularQueueList;

bool is_empty (CircularQueueList *q){
    return q->rear==NULL;
}

void enqueue(CircularQueueList *q){
    Node *newNode = (Node *)malloc(sizeof(Node));

    int val;
    printf("Enter data to be enqueued: ");
    scanf("%d",&val);

    newNode->data=val;
    if(is_empty(q)){
        newNode->next=newNode;
        q->rear=newNode;
    }
    else{
        newNode->next=q->rear->next;//newNode points to first element
        q->rear->next=newNode;//2nd last node points to newNode  
        q->rear=newNode;//make newNode as rear
    }
    q->count++;
    printf("Enqueued %d\n",val);
}
void dequeue(CircularQueueList *q){
    if(is_empty(q)==1)
    {
        printf("Queue is already empty\n");
        return;
    }
    Node *front=q->rear->next;
    int val=front->data;
    printf("Dequeued value is %d\n",val);
    if(front==q->rear){
        q->rear=NULL;
    }
    else{
        q->rear->next=front->next;
    }
    free(front);
    q->count--;
}
void print_Queue(CircularQueueList *q)
{
    if(q->rear==NULL){
        printf("Queue is empty\n");
        return;
    }
    Node *temp=q->rear->next;

    printf("Queue elements are:- ");
    do{
        printf("%d ",temp->data);
        temp=temp->next;
    }while(q->rear->next!=temp);

    printf("\n");
}

int main()
{
    CircularQueueList q;
    q.rear=NULL;
    q.count=0;

    while(1)
    {
        printf("\nEnter 1 to Enque\n");
        printf("Enter 2 to Dequeue\n");
        printf("Enter 3 to Display element\n");
        printf("Enter 4 to Exit element\n");

        int n;
        scanf("%d",&n);
        if(n==1)
            enqueue(&q);
        else if(n==2)
            dequeue(&q);
        else if(n==3)
            print_Queue(&q);
        else
        {
            printf("Exit");
            return 0;
        }
    }
    return 0;
}