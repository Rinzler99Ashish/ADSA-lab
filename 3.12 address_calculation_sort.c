#include <stdio.h>
#include <stdlib.h>

#define SIZE 10   // number of address buckets

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Insert into bucket's linked list, keeping it sorted
void insertSorted(Node** head, int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;

    if (*head == NULL || data < (*head)->data) {
        newNode->next = *head;
        *head = newNode;
        return;
    }
    Node* cur = *head;
    while (cur->next != NULL && cur->next->data < data)
        cur = cur->next;
    newNode->next = cur->next;
    cur->next = newNode;
}

// Hash function: maps value to bucket index [0, SIZE-1]
int hashFunction(int val, int min, int range) {
    return (int)(((double)(val - min) / range) * (SIZE - 1));
}

void addressCalculationSort(int arr[], int n) {
    Node* buckets[SIZE] = {0};

    int min = arr[0], max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    int range = (max - min) > 0 ? (max - min) : 1;  // avoid div-by-zero

    // Place each value into its address bucket
    for (int i = 0; i < n; i++) {
        int addr = hashFunction(arr[i], min, range);
        insertSorted(&buckets[addr], arr[i]);
    }

    // Collect buckets back into arr, freeing nodes as we go
    int idx = 0;
    for (int i = 0; i < SIZE; i++) {
        Node* cur = buckets[i];
        while (cur != NULL) {
            arr[idx++] = cur->data;
            Node* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
}

int main() {
    int arr[] = {-5, 3, -2, 0, 7, -1, 4, 15, -10};
    int n = sizeof(arr) / sizeof(arr[0]);

    addressCalculationSort(arr, n);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}