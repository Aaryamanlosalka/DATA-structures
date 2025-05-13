#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ZONE_NAME 100

typedef struct Node {
    char zoneName[MAX_ZONE_NAME];
    int waterNeed;
    struct Node *left, *right;
} Node;

Node* createNode(const char *name, int need) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) {
        printf("Error: Memory allocation failed for zone %s\n", name);
        return NULL;
    }
    strncpy(node->zoneName, name, MAX_ZONE_NAME);
    node->zoneName[MAX_ZONE_NAME - 1] = '\0';
    node->waterNeed = need;
    node->left = node->right = NULL;
    return node;
}

Node* insertNode(Node *root, const char *name, int need) {
    if (!root) {
        printf("Zone '%s' added with water need %d.\n", name, need);
        return createNode(name, need);
    }
    if (need < root->waterNeed)
        root->left = insertNode(root->left, name, need);
    else if (need > root->waterNeed)
        root->right = insertNode(root->right, name, need);
    else
        printf("Warning: Zone %s has same water need as existing zone. Ignoring.\n", name);
    return root;
}

Node* minValueNode(Node *node) {
    Node *current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

Node* deleteNode(Node *root, const char *name) {
    if (!root)
        return root;
    int cmp = strcmp(name, root->zoneName);
    if (cmp < 0)
        root->left = deleteNode(root->left, name);
    else if (cmp > 0)
        root->right = deleteNode(root->right, name);
    else {
        if (!root->left) {
            Node *temp = root->right;
            printf("Removed zone: %s (Water Need: %d)\n", root->zoneName, root->waterNeed);
            free(root);
            return temp;
        }
        else if (!root->right) {
            Node *temp = root->left;
            printf("Removed zone: %s (Water Need: %d)\n", root->zoneName, root->waterNeed);
            free(root);
            return temp;
        }
        Node *temp = minValueNode(root->right);
        strncpy(root->zoneName, temp->zoneName, MAX_ZONE_NAME);
        root->waterNeed = temp->waterNeed;
        root->right = deleteNode(root->right, temp->zoneName);
    }
    return root;
}

Node* updateWaterNeed(Node *root, const char *name, int newNeed) {
    root = deleteNode(root, name);
    root = insertNode(root, name, newNeed);
    return root;
}

void scheduleWatering(Node *root) {
    if (root) {
        scheduleWatering(root->left);
        printf(" - Water %s (Need: %d)\n", root->zoneName, root->waterNeed);
        scheduleWatering(root->right);
    }
}

void displaySchedule(Node *root) {
    if (!root) {
        printf("No zones to schedule.\n");
        return;
    }
    printf("Irrigation Plan (Low to High Need):\n");
    scheduleWatering(root);
}

void displayMenu() {
    printf("------- SMART FARM IRRIGATION SYSTEM -------\n");
    printf("1. Add Farm Zone\n");
    printf("2. View Watering Schedule\n");
    printf("3. Update Water Need\n");
    printf("4. Remove Zone\n");
    printf("5. Exit\n");
}

void simulateUserAction(Node **root, int choice, const char *zoneName, int waterNeed) {
    printf("Enter your choice: %d\n", choice);
    switch (choice) {
        case 1:
            if (zoneName) {
                printf("Enter zone name: %s\n", zoneName);
                printf("Enter water need: %d\n", waterNeed);
                *root = insertNode(*root, zoneName, waterNeed);
            }
            break;
        case 2:
            displaySchedule(*root);
            break;
        case 3:
            if (zoneName) {
                printf("Enter zone name to update: %s\n", zoneName);
                printf("Enter new water need: %d\n", waterNeed);
                *root = updateWaterNeed(*root, zoneName, waterNeed);
            }
            break;
        case 4:
            if (zoneName) {
                printf("Enter zone name to remove: %s\n", zoneName);
                *root = deleteNode(*root, zoneName);
            }
            break;
        case 5:
            printf("EXITING FARM SYSTEM\n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
    printf("\n");
}

int main() {
    Node *root = NULL;

    displayMenu();
    simulateUserAction(&root, 1, "Zone A", 80);

    displayMenu();
    simulateUserAction(&root, 1, "Zone B", 50);

    displayMenu();
    simulateUserAction(&root, 2, NULL, 0);

    displayMenu();
    simulateUserAction(&root, 3, "Zone B", 70);

    displayMenu();
    simulateUserAction(&root, 2, NULL, 0); // Show schedule after update

    displayMenu();
    simulateUserAction(&root, 1, "Zone C", 90);

    displayMenu();
    simulateUserAction(&root, 4, "Zone A", 0);

    displayMenu();
    simulateUserAction(&root, 2, NULL, 0); // Show schedule after removal

    displayMenu();
    simulateUserAction(&root, 5, NULL, 0);

    return 0;
}