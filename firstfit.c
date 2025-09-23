#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    int start_address;
    int size;
    struct Block* next;
    struct Block* prev;
} Block;

Block* head = NULL;

Block* create_block(int start, int size) {
    Block* new_block = (Block*)malloc(sizeof(Block));
    if (!new_block) {
        printf("Memory allocation failed for block creation.\n");
        exit(1);
    }
    new_block->start_address = start;
    new_block->size = size;
    new_block->next = NULL;
    new_block->prev = NULL;
    return new_block;
}

void add_block(int start, int size) {
    Block* new_block = create_block(start, size);

    if (head == NULL) {
        head = new_block;
        return;
    }

    Block* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = new_block;
    new_block->prev = temp;
}

void display_free_blocks() {
    printf("\nFree Memory Blocks:\n");
    Block* temp = head;
    if (temp == NULL) {
        printf("No free blocks available.\n");
        return;
    }
    while (temp != NULL) {
        printf("Start: %d, Size: %d\n", temp->start_address, temp->size);
        temp = temp->next;
    }
    printf("\n");
}

void first_fit_allocate(int request_size) {
    Block* temp = head;

    while (temp != NULL) {
        if (temp->size >= request_size) {
            printf("Memory allocated at address: %d\n", temp->start_address);

            if (temp->size == request_size) {
                // Perfect fit - remove this block
                if (temp->prev == NULL) {
                    head = temp->next;
                    if (head != NULL)
                        head->prev = NULL;
                } else if (temp->next != NULL) {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                } else {
                    temp->prev->next = NULL;
                }

                free(temp);
            } else {
                // Partial allocation - adjust start address and size
                temp->start_address += request_size;
                temp->size -= request_size;
            }
            return;
        }
        temp = temp->next;
    }
    printf("Allocation failed: No sufficient memory block available\n");
}

int main() {
    int n, i, start, size, request;

    printf("Enter the number of initial free memory blocks: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter start address and size of block %d: ", i + 1);
        scanf("%d %d", &start, &size);
        add_block(start, size);
    }

    display_free_blocks();

    char choice;
    do {
        printf("Enter size of process to allocate: ");
        scanf("%d", &request);
        first_fit_allocate(request);
        display_free_blocks();

        printf("Do you want to allocate another process? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
