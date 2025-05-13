#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUESTS 100
#define ID_LENGTH 100

typedef struct {
    char requestID[ID_LENGTH];
} Request;

typedef struct {
    Request requests[MAX_REQUESTS];
    int front, rear, count;
} RequestQueue;

void initializeQueue(RequestQueue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

int isFull(RequestQueue *q) {
    return q->count == MAX_REQUESTS;
}

int isEmpty(RequestQueue *q) {
    return q->count == 0;
}

void enqueue(RequestQueue *q, const char *id) {
    if (isFull(q)) {
        printf("Error: Queue is full. Request %s cannot be added.\n", id);
        return;
    }
    q->rear = (q->rear + 1) % MAX_REQUESTS;
    strncpy(q->requests[q->rear].requestID, id, ID_LENGTH);
    q->requests[q->rear].requestID[ID_LENGTH - 1] = '\0';
    q->count++;
    printf("Request '%s' added to queue.\n", id);
}

void dequeue(RequestQueue *q) {
    if (isEmpty(q)) {
        printf("Error: No requests to process.\n");
        return;
    }
    printf("Dispatched drone for request '%s'.\n", q->requests[q->front].requestID);
    q->front = (q->front + 1) % MAX_REQUESTS;
    q->count--;
}

void viewQueue(RequestQueue *q) {
    if (isEmpty(q)) {
        printf("No pending requests.\n");
        return;
    }
    printf("Pending Requests (Oldest to Newest):\n");
    int i, idx;
    for (i = 0; i < q->count; i++) {
        idx = (q->front + i) % MAX_REQUESTS;
        printf(" - %s\n", q->requests[idx].requestID);
    }
}

void viewQueueLength(RequestQueue *q) {
    printf("Current queue length: %d\n", q->count);
}

void displayMenu() {
    printf("------- EMERGENCY DRONE DISPATCH -------\n");
    printf("1. Add Emergency Request\n");
    printf("2. View Pending Requests\n");
    printf("3. Dispatch Next Drone\n");
    printf("4. View Queue Length\n");
    printf("5. Exit\n");
}

void simulateUserAction(RequestQueue *q, int choice, const char *requestID) {
    printf("Enter your choice: %d\n", choice);
    switch (choice) {
        case 1:
            if (requestID) {
                printf("Enter request ID: %s\n", requestID);
                enqueue(q, requestID);
            }
            break;
        case 2:
            viewQueue(q);
            break;
        case 3:
            dequeue(q);
            break;
        case 4:
            viewQueueLength(q);
            break;
        case 5:
            printf("CLOSING DRONE SYSTEM\n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
    printf("\n");
}

int main() {
    RequestQueue queue;
    initializeQueue(&queue);

    displayMenu();
    simulateUserAction(&queue, 1, "REQ001");

    displayMenu();
    simulateUserAction(&queue, 1, "REQ002");

    displayMenu();
    simulateUserAction(&queue, 2, NULL);

    displayMenu();
    simulateUserAction(&queue, 4, NULL);

    displayMenu();
    simulateUserAction(&queue, 3, NULL);

    displayMenu();
    simulateUserAction(&queue, 2, NULL); // Show queue after dispatching

    displayMenu();
    simulateUserAction(&queue, 1, "REQ003");

    displayMenu();
    simulateUserAction(&queue, 4, NULL); // Show queue length after adding

    displayMenu();
    simulateUserAction(&queue, 5, NULL);

    return 0;
}