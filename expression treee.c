#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// ------------------ INFIX TO POSTFIX -------------------
int precedence(char op) {
    if(op == '^') return 3;
    if(op == '*' || op == '/') return 2;
    if(op == '+' || op == '-') return 1;
    return 0;
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

void infixToPostfix(char infix[], char postfix[]) {
    char stack[MAX];
    int top = -1, i = 0, j = 0;
    char ch;

    while((ch = infix[i++]) != '\0') {
        if(isalnum(ch)) {
            postfix[j++] = ch;
        }
        else if(ch == '(') {
            stack[++top] = ch;
        }
        else if(ch == ')') {
            while(top != -1 && stack[top] != '(') {
                postfix[j++] = stack[top--];
            }
            if(top != -1) top--; // pop '('
        }
        else if(isOperator(ch)) {
            while(top != -1 && precedence(stack[top]) >= precedence(ch)) {
                postfix[j++] = stack[top--];
            }
            stack[++top] = ch;
        }
    }

    while(top != -1) {
        postfix[j++] = stack[top--];
    }

    postfix[j] = '\0';
}

// ------------------ EXPRESSION TREE FROM POSTFIX -------------------

struct Node {
    char data;
    struct Node *left, *right;
};

struct StackNode {
    struct Node* data;
    struct StackNode* next;
};

struct StackNode* top = NULL;

struct Node* createNode(char value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void push(struct Node* treeNode) {
    struct StackNode* temp = (struct StackNode*)malloc(sizeof(struct StackNode));
    temp->data = treeNode;
    temp->next = top;
    top = temp;
}

struct Node* pop() {
    if(top == NULL)
        return NULL;

    struct StackNode* temp = top;
    struct Node* result = top->data;
    top = top->next;
    free(temp);
    return result;
}

struct Node* createExpressionTree(char postfix[]) {
    int i = 0;
    char symbol;
    while((symbol = postfix[i]) != '\0') {
        if(isalnum(symbol)) {
            struct Node* operandNode = createNode(symbol);
            push(operandNode);
        } else {
            struct Node* operatorNode = createNode(symbol);
            operatorNode->right = pop();
            operatorNode->left = pop();
            push(operatorNode);
        }
        i++;
    }
    return pop();
}

// ------------------ TRAVERSALS -------------------

void inorder(struct Node* root) {
    if (root != NULL) {
        if (root->left && root->right) printf("(");
        inorder(root->left);
        printf("%c", root->data);
        inorder(root->right);
        if (root->left && root->right) printf(")");
    }
}

void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%c", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%c", root->data);
    }
}

// ------------------ MAIN FUNCTION -------------------

int main() {
    struct Node* root = NULL;
    char infix[100], postfix[100];
    int choice;

    // Step 1: Input Infix
    printf("Enter an infix expression: ");
    scanf("%s", infix);

    // Step 2: Convert to Postfix
    infixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);

    // Step 3: Build expression tree from postfix
    root = createExpressionTree(postfix);
    printf("Expression tree created from postfix expression.\n");

    // Step 4: Allow traversal options on postfix tree
    do {
        printf("\nMenu\n");
        printf("1. Inorder Traversal (Postfix Expression Tree)\n");
        printf("2. Preorder Traversal (Postfix Expression Tree)\n");
        printf("3. Postorder Traversal (Postfix Expression Tree)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear buffer

        switch(choice) {
            case 1:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 2:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;
            case 3:
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }

    } while(1);

    return 0;
}