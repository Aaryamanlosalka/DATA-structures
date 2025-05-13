#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEVEL_NAME 100

typedef struct Node {
    char levelName[MAX_LEVEL_NAME];
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} LevelList;

void initialize(LevelList *list) {
    list->head = NULL;
}

void insertLevel(LevelList *list, const char *name) {
    if (!name) {
        printf("Error: Level name cannot be NULL.\n");
        return;
    }
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Error: Memory allocation failed for level %s\n", name);
        return;
    }
    strncpy(newNode->levelName, name, MAX_LEVEL_NAME);
    newNode->levelName[MAX_LEVEL_NAME - 1] = '\0';
    newNode->next = list->head;
    list->head = newNode;
    printf("Level '%s' added.\n", name); // Fixed: Added 'name' as argument to printf
}

void completeLevel(LevelList *list) {
    if (!list->head) {
        printf("Error: No levels to complete.\n");
        return;
    }
    Node *temp = list->head;
    list->head = list->head->next;
    printf("Completed level '%s'.\n", temp->levelName);
    free(temp);
}

void displayLevels(LevelList *list) {
    if (!list->head) {
        printf("No levels available.\n");
        return;
    }
    printf("Current Levels (Most Recent to Oldest):\n");
    Node *current = list->head;
    while (current) {
        printf(" - %s\n", current->levelName);
        current = current->next;
    }
}

int countLevels(LevelList *list) {
    int count = 0;
    Node *current = list->head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

void freeList(LevelList *list) {
    Node *current = list->head;
    while (current) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
}

void displayMenu() {
    printf("------- VR GAME LEVEL TRACKER -------\n");
    printf("1. Add New Level\n");
    printf("2. View Current Levels\n");
    printf("3. Complete Next Level\n");
    printf("4. Count Levels\n");
    printf("5. Exit\n");
}

void simulateUserAction(LevelList *list, int choice, const char *levelName) {
    printf("Select an option: %d\n", choice);
    switch (choice) {
        case 1:
            if (levelName) {
                printf("Enter level name: %s\n", levelName);
                insertLevel(list, levelName);
            }
            break;
        case 2:
            displayLevels(list);
            break;
        case 3:
            completeLevel(list);
            break;
        case 4:
            printf("Total levels: %d\n", countLevels(list));
            break;
        case 5:
            printf("EXITING GAME SYSTEM\n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
    printf("\n");
}

int main() {
    LevelList game;
    initialize(&game);

    displayMenu();
    simulateUserAction(&game, 1, "Level 1");

    displayMenu();
    simulateUserAction(&game, 1, "Level 2");

    displayMenu();
    simulateUserAction(&game, 2, NULL);

    displayMenu();
    simulateUserAction(&game, 4, NULL);

    displayMenu();
    simulateUserAction(&game, 3, NULL);

    displayMenu();
    simulateUserAction(&game, 2, NULL);

    displayMenu();
    simulateUserAction(&game, 1, "Level 3");

    displayMenu();
    simulateUserAction(&game, 4, NULL);

    displayMenu();
    simulateUserAction(&game, 5, NULL);

    freeList(&game);

    return 0;
}