#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure for triplet
typedef struct {
    int row;
    int col;
    int val;
} Triplet;

// Function to convert normal matrix to triplet
int createTriplet(int matrix[10][10], int rows, int cols, Triplet triplet[]) {
    int k = 1; // Start from 1, 0 is metadata
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                triplet[k].row = i;
                triplet[k].col = j;
                triplet[k].val = matrix[i][j];
                k++;
            }
        }
    }
    triplet[0].row = rows;
    triplet[0].col = cols;
    triplet[0].val = k - 1;
    return k; // Total elements in triplet
}

// Function to display triplet matrix
void displayTriplet(Triplet triplet[], int size) {
    printf("Row  Col  Val\n");
    for (int i = 0; i < size; i++) {
        printf("%-5d%-5d%-5d\n", triplet[i].row, triplet[i].col, triplet[i].val);
    }
}

// Function to add two sparse matrices
int addTriplets(Triplet a[], Triplet b[], Triplet result[]) {
    if (a[0].row != b[0].row || a[0].col != b[0].col) {
        printf("Matrix dimensions do not match!\n");
        return 0;
    }

    result[0].row = a[0].row;
    result[0].col = a[0].col;

    int i = 1, j = 1, k = 1;
    while (i <= a[0].val && j <= b[0].val) {
        if (a[i].row == b[j].row && a[i].col == b[j].col) {
            int sum = a[i].val + b[j].val;
            if (sum != 0) {
                result[k].row = a[i].row;
                result[k].col = a[i].col;
                result[k].val = sum;
                k++;
            }
            i++; j++;
        } else if ((a[i].row < b[j].row) || (a[i].row == b[j].row && a[i].col < b[j].col)) {
            result[k++] = a[i++];
        } else {
            result[k++] = b[j++];
        }
    }

    while (i <= a[0].val) result[k++] = a[i++];
    while (j <= b[0].val) result[k++] = b[j++];

    result[0].val = k - 1;
    return k;
}

// Function to transpose sparse matrix
int transposeTriplet(Triplet a[], Triplet trans[]) {
    trans[0].row = a[0].col;
    trans[0].col = a[0].row;
    trans[0].val = a[0].val;

    int k = 1;
    for (int col = 0; col < a[0].col; col++) {
        for (int i = 1; i <= a[0].val; i++) {
            if (a[i].col == col) {
                trans[k].row = a[i].col;
                trans[k].col = a[i].row;
                trans[k].val = a[i].val;
                k++;
            }
        }
    }
    return k;
}

// Main function
int main() {
    int A[10][10] = {
        {0, 0, 3},
        {4, 0, 0},
        {0, 5, 6}
    };

    int B[10][10] = {
        {0, 0, 1},
        {1, 0, 0},
        {0, -5, 0}
    };

    Triplet tripletA[MAX], tripletB[MAX], result[MAX], transpose[MAX];
    int sizeA = createTriplet(A, 3, 3, tripletA);
    int sizeB = createTriplet(B, 3, 3, tripletB);

    printf("\nTriplet Representation of Matrix A:\n");
    displayTriplet(tripletA, sizeA);

    printf("\nTriplet Representation of Matrix B:\n");
    displayTriplet(tripletB, sizeB);

    int sizeAdd = addTriplets(tripletA, tripletB, result);
    printf("\nAddition Result (Triplet Form):\n");
    displayTriplet(result, sizeAdd);

    int sizeTranspose = transposeTriplet(tripletA, transpose);
    printf("\nTranspose of Matrix A (Triplet Form):\n");
    displayTriplet(transpose, sizeTranspose);

    return 0;
}
