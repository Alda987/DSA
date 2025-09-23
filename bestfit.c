#include <stdio.h>
#include <stdlib.h>

// Structure for a memory block node
typedef struct Node {
    int start_address;
    int size;
    struct Node* prev;
    struct Node* next;
} Node;

Node* head = NULL;

// Function to create a new memory block node
Node* create_block(int start, int size) {
    Node* new_block = (Node*)malloc(sizeof(Node));
    if (!new_block) {
        printf("Memory allocation failed for new block.\n");
        exit(1);
    }
    new_block->start_address = start;
    new_block->size = size;
    new_block->prev = NULL;
    new_block->next = NULL;
    return new_block;
}

// Function to add a block to the end of the free list
void add_block(int start, int size) {
    Node* new_block = create_block(start, size);
    if (head == NULL) {
        head = new_block;
        return;
    }

    Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = new_block;
    new_block->prev = temp;
}

// Function to display all free memory blocks
void display_free_blocks() {
    Node* temp = head;
    if (temp == NULL) {
        printf("No free memory blocks available.\n");
        return;
    }
    printf("\nFree Memory Blocks:\n");
    printf("Start Address\tSize\n");
    while (temp != NULL) {
        printf("%d\t\t%d\n", temp->start_address, temp->size);
        temp = temp->next;
    }
}

// Function to allocate memory using Best Fit
void best_fit_allocate(int request_size) {
    Node* temp = head;
    Node* best_block = NULL;

    // Find smallest suitable block
    while (temp != NULL) {
        if (temp->size >= request_size) {
            if (best_block == NULL || temp->size < best_block->size) {
                best_block = temp;
            }
        }
        temp = temp->next;
    }

    if (best_block == NULL) {
        printf("Allocation failed: No sufficient memory block available.\n");
        return;
    }

    printf("Memory allocated at address %d\n", best_block->start_address);

    if (best_block->size == request_size) {
        // Remove the node from the free list
        if (best_block->prev == NULL && best_block->next == NULL) {
            // Only node
            head = NULL;
        } else if (best_block->prev == NULL) {
            // Head node
            head = best_block->next;
            head->prev = NULL;
        } else if (best_block->next == NULL) {
            // Last node
            best_block->prev->next = NULL;
        } else {
            // Middle node
            best_block->prev->next = best_block->next;
            best_block->next->prev = best_block->prev;
        }
        free(best_block);
    } else {
        // Block larger than requested, split it
        best_block->start_address += request_size;
        best_block->size -= request_size;
    }
}

int main() {
    int choice;
    int start, size, request_size, n, i;

    printf("Best Fit Memory Allocation using Doubly Linked List\n");

    // Input initial free memory blocks
    printf("Enter number of free memory blocks to add: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Enter start address and size of block %d: ", i + 1);
        scanf("%d%d", &start, &size);
        add_block(start, size);
    }

    display_free_blocks();

    while (1) {
        printf("\nMenu:\n");
        printf("1. Allocate memory\n");
        printf("2. Display free blocks\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter size of memory to allocate: ");
                scanf("%d", &request_size);
                best_fit_allocate(request_size);
                break;
            case 2:
                display_free_blocks();
                break;
            case 3:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

