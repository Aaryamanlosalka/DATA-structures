#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 101
#define MAX_NAME_LEN 100
#define MAX_PREF_LEN 50

typedef struct {
    char name[MAX_NAME_LEN];
    char preference[MAX_PREF_LEN];
} User;

typedef struct UserNode {
    char userID[MAX_NAME_LEN];
    User user;
    struct UserNode *next;
} UserNode;

UserNode *hashTable[TABLE_SIZE];

unsigned int hash(const char *key) {
    unsigned int hashVal = 0;
    while (*key) hashVal = (hashVal * 31 + *key++) % TABLE_SIZE;
    return hashVal;
}

void initializeHashTable() {
    memset(hashTable, 0, sizeof(hashTable));
}

void insertUser(const char *userID, User user) {
    unsigned int index = hash(userID);
    UserNode *newNode = (UserNode *)malloc(sizeof(UserNode));
    if (!newNode) {
        printf("Error: Memory allocation failed for user %s\n", userID);
        return;
    }
    strncpy(newNode->userID, userID, MAX_NAME_LEN);
    newNode->userID[MAX_NAME_LEN - 1] = '\0';
    newNode->user = user;
    newNode->user.name[MAX_NAME_LEN - 1] = '\0';
    newNode->user.preference[MAX_PREF_LEN - 1] = '\0';
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
    printf("User '%s' added with preference '%s'.\n", user.name, user.preference);
}

void findMatch(const char *userID, const char *preference) {
    printf("Finding matches for user '%s'...\n", userID);
    unsigned int index = hash(userID);
    UserNode *node = hashTable[index];
    while (node && strcmp(node->userID, userID) != 0) node = node->next;
    if (!node) {
        printf("Error: User %s not found.\n", userID);
        return;
    }
    printf("Matches for %s preferring %s:\n", node->user.name, preference);
    int found = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        UserNode *current = hashTable[i];
        while (current) {
            if (strcmp(current->user.preference, preference) == 0 && strcmp(current->userID, userID) != 0) {
                printf(" * %s (ID: %s)\n", current->user.name, current->userID);
                found++;
            }
            current = current->next;
        }
    }
    if (!found) {
        printf("No matches found for preference '%s'.\n", preference);
    }
}

void listUsers() {
    int found = 0;
    printf("All Registered Users:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        UserNode *current = hashTable[i];
        while (current) {
            printf(" - %s (ID: %s, Preference: %s)\n", current->user.name, current->userID, current->user.preference);
            found++;
            current = current->next;
        }
    }
    if (!found) {
        printf("No users registered.\n");
    }
}

void deleteUser(const char *userID) {
    unsigned int index = hash(userID);
    UserNode *current = hashTable[index];
    UserNode *prev = NULL;
    while (current && strcmp(current->userID, userID) != 0) {
        prev = current;
        current = current->next;
    }
    if (!current) {
        printf("Error: User %s not found.\n", userID);
        return;
    }
    if (prev) {
        prev->next = current->next;
    } else {
        hashTable[index] = current->next;
    }
    printf("User '%s' removed.\n", current->user.name);
    free(current);
}

void displayMenu() {
    printf("------- TRAVEL BUDDY MATCHER -------\n");
    printf("1. Add User\n");
    printf("2. Find Travel Buddies\n");
    printf("3. List All Users\n");
    printf("4. Remove User\n");
    printf("5. Exit\n");
}

void simulateUserAction(const char *userID, User *user, int choice, const char *preference) {
    printf("Enter your choice: %d\n", choice);
    switch (choice) {
        case 1:
            if (userID && user) {
                printf("Enter user name: %s\n", user->name);
                printf("Enter preference: %s\n", user->preference);
                insertUser(userID, *user);
            }
            break;
        case 2:
            if (userID && preference) {
                printf("Enter user ID to match: %s\n", userID);
                printf("Enter preference to match: %s\n", preference);
                findMatch(userID, preference);
            }
            break;
        case 3:
            listUsers();
            break;
        case 4:
            if (userID) {
                printf("Enter user ID to remove: %s\n", userID);
                deleteUser(userID);
            }
            break;
        case 5:
            printf("EXITING MATCHER SYSTEM\n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
    printf("\n");
}

int main() {
    initializeHashTable();

    User user1 = {"Alice", "Hiking"};
    User user2 = {"Bob", "Hiking"};
    User user3 = {"Charlie", "Sightseeing"};

    displayMenu();
    simulateUserAction("alice@example.com", &user1, 1, NULL);

    displayMenu();
    simulateUserAction("bob@example.com", &user2, 1, NULL);

    displayMenu();
    simulateUserAction("charlie@example.com", &user3, 1, NULL);

    displayMenu();
    simulateUserAction(NULL, NULL, 3, NULL);

    displayMenu();
    simulateUserAction("alice@example.com", NULL, 2, "Hiking");

    displayMenu();
    simulateUserAction("bob@example.com", NULL, 4, NULL);

    displayMenu();
    simulateUserAction(NULL, NULL, 5, NULL);

    return 0;
}