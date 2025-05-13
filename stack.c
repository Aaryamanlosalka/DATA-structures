#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define TASK_NAME_LENGTH 100

typedef struct {
    char tasks[MAX_TASKS][TASK_NAME_LENGTH];
    int top;
} TaskStack;

void initialize(TaskStack *stack) {
    stack->top = -1;
}

int isFull(TaskStack *stack) {
    return stack->top == MAX_TASKS - 1;
}

int isEmpty(TaskStack *stack) {
    return stack->top == -1;
}

void push(TaskStack *stack, const char *taskName) {
    if (isFull(stack)) {
        printf("Error: Task stack is full. Cannot add task: %s\n", taskName);
        return;
    }
    stack->top++;
    strncpy(stack->tasks[stack->top], taskName, TASK_NAME_LENGTH);
    stack->tasks[stack->top][TASK_NAME_LENGTH - 1] = '\0';
    printf("Task '%s' added.\n", taskName);
}

void pop(TaskStack *stack) {
    if (isEmpty(stack)) {
        printf("Error: No tasks to execute.\n");
        return;
    }
    printf("Executing: %s\n", stack->tasks[stack->top]);
    stack->top--;
}

void viewTasks(TaskStack *stack) {
    if (isEmpty(stack)) {
        printf("No pending tasks.\n");
        return;
    }
    printf("Pending Tasks (Top to Bottom):\n");
    for (int i = stack->top; i >= 0; i--) {
        printf(" - %s\n", stack->tasks[i]);
    }
}

void startLaunch(TaskStack *stack) {
    printf("Initiating Launch Sequence...\n\n");
    while (!isEmpty(stack)) {
        pop(stack);
    }
    printf("\nALL SYSTEMS READY! 🚀 Launch Successful\n");
}

void clearTasks(TaskStack *stack) {
    stack->top = -1;
    printf("All tasks cleared.\n");
}

void displayMenu() {
    printf("===== SPACE ROCKET LAUNCH SYSTEM =====\n");
    printf("1. Add Preparation Task\n");
    printf("2. View Pending Tasks\n");
    printf("3. Start Launch Sequence\n");
    printf("4. Clear All Tasks\n");
    printf("5. Exit\n");
}

void simulateUserAction(TaskStack *stack, int choice, const char *task) {
    printf("Enter your choice: %d\n", choice);
    switch (choice) {
        case 1:
            if (task) {
                printf("Enter task name: %s\n", task);
                push(stack, task);
            }
            break;
        case 2:
            viewTasks(stack);
            break;
        case 3:
            startLaunch(stack);
            break;
        case 4:
            clearTasks(stack);
            break;
        case 5:
            printf("SYSTEM SHUTTING DOWN\n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
    printf("\n");
}

int main() {
    TaskStack launch;
    initialize(&launch);

    displayMenu();
    simulateUserAction(&launch, 1, "to check fuel");

    displayMenu();
    simulateUserAction(&launch, 1, "to check navigation");

    displayMenu();
    simulateUserAction(&launch, 2, NULL);

    displayMenu();
    simulateUserAction(&launch, 4, NULL);

    displayMenu();
    simulateUserAction(&launch, 2, NULL); // Show empty task list after clearing

    displayMenu();
    simulateUserAction(&launch, 1, "to check systems");

    displayMenu();
    simulateUserAction(&launch, 3, NULL);

    displayMenu();
    simulateUserAction(&launch, 5, NULL);

    return 0;
}