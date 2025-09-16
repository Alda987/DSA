#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff;
    int exp;
    struct Node* next;
} Node;


Node* createNode(int coeff, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}


void insertTerm(Node** poly, int coeff, int exp) {
    if (coeff == 0) return;  
    Node* newNode = createNode(coeff, exp);
    if (*poly == NULL || (*poly)->exp < exp) {
        newNode->next = *poly;
        *poly = newNode;
    } else {
        Node* temp = *poly;
        while (temp->next != NULL && temp->next->exp > exp) {
            temp = temp->next;
        }

        if (temp->next != NULL && temp->next->exp == exp) {
            temp->next->coeff += coeff;
            if (temp->next->coeff == 0) {
               
                Node* toDelete = temp->next;
                temp->next = temp->next->next;
                free(toDelete);
            }
            free(newNode);
        } else {
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
}

Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;

    while (poly1 && poly2) {
        if (poly1->exp == poly2->exp) {
            int sumCoeff = poly1->coeff + poly2->coeff;
            if (sumCoeff != 0)
                insertTerm(&result, sumCoeff, poly1->exp);
            poly1 = poly1->next;
            poly2 = poly2->next;
        } else if (poly1->exp > poly2->exp) {
            insertTerm(&result, poly1->coeff, poly1->exp);
            poly1 = poly1->next;
        } else {
            insertTerm(&result, poly2->coeff, poly2->exp);
            poly2 = poly2->next;
        }
    }

    while (poly1) {
        insertTerm(&result, poly1->coeff, poly1->exp);
        poly1 = poly1->next;
    }

    while (poly2) {
        insertTerm(&result, poly2->coeff, poly2->exp);
        poly2 = poly2->next;
    }

    return result;
}

void printPolynomial(Node* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }

    while (poly) {
        if (poly->coeff > 0 && poly != NULL && poly != poly->next)
            printf("+");

        printf("%dx^%d ", poly->coeff, poly->exp);
        poly = poly->next;
    }
    printf("\n");
}


void freePolynomial(Node* poly) {
    Node* temp;
    while (poly) {
        temp = poly;
        poly = poly->next;
        free(temp);
    }
}

int main() {
    Node *poly1 = NULL, *poly2 = NULL, *result = NULL;
    int n, coeff, exp;

    
    printf("Enter number of terms for first polynomial: ");
    scanf("%d", &n);
    printf("Enter terms in format: coefficient exponent\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coeff, &exp);
        insertTerm(&poly1, coeff, exp);
    }

   
    printf("Enter number of terms for second polynomial: ");
    scanf("%d", &n);
    printf("Enter terms in format: coefficient exponent\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coeff, &exp);
        insertTerm(&poly2, coeff, exp);
    }

    
    printf("First Polynomial: ");
    printPolynomial(poly1);

    printf("Second Polynomial: ");
    printPolynomial(poly2);

    
    result = addPolynomials(poly1, poly2);

    
    printf("Resultant Polynomial after addition: ");
    printPolynomial(result);

    
    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(result);

    return 0;
}

