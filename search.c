#include <stdio.h>
#include <stdlib.h>

// Define the node structure
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert function
Node* insert(Node* root, int data) {
    if (root == NULL) {
        // Tree is empty, create a new node
        return createNode(data);
    }
    if (data < root->data) {
        // Insert in left subtree
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        // Insert in right subtree
        root->right = insert(root->right, data);
    }
    // If data == root->data, do nothing (no duplicates)
    return root;
}

// Search function
Node* search(Node* root, int data) {
    if (root == NULL || root->data == data)
        return root;

    if (data < root->data)
        return search(root->left, data);
    else
        return search(root->right, data);
}

// Find minimum value node in subtree
Node* findMin(Node* root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

// Delete function
Node* deleteNode(Node* root, int data) {
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        // Node found

        // Case 1: No child or one child
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Case 2: Node with two children
        // Get inorder successor (smallest in the right subtree)
        Node* temp = findMin(root->right);

        // Copy the inorder successor's data to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Inorder traversal (for testing)
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Main function to demonstrate the BST
int main() {
    Node* root = NULL;
    int choice, val;
    Node* found;

    while (1) {
        printf("\n1. Insert\n2. Search\n3. Delete\n4. Inorder traversal\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                root = insert(root, val);
                printf("%d inserted.\n", val);
                break;

            case 2:
                printf("Enter value to search: ");
                scanf("%d", &val);
                found = search(root, val);
                if (found)
                    printf("%d found in the tree.\n", val);
                else
                    printf("%d not found in the tree.\n", val);
                break;

            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                root = deleteNode(root, val);
                printf("%d deleted (if it existed).\n", val);
                break;

            case 4:
                printf("Inorder traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
