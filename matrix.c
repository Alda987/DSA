#include <stdio.h>

#define MAX 100

void inputMatrix(int mat[MAX][MAX], int rows, int cols) {
    printf("Enter the elements of the matrix (row by row):\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
}

void addMatrices(int mat1[MAX][MAX], int mat2[MAX][MAX], int res[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            res[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

void transposeMatrix(int mat[MAX][MAX], int transposed[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposed[j][i] = mat[i][j];
        }
    }
}

void printMatrix(int mat[MAX][MAX], int rows, int cols) {
    printf("Matrix form:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void printTupleForm(int mat[MAX][MAX], int rows, int cols) {
    int count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (mat[i][j] != 0) {
                count++;
            }
        }
    }

    printf("Tuple form (rows, cols, non-zero values):\n");
    printf("(%d, %d, %d)\n", rows, cols, count);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (mat[i][j] != 0) {
                printf("(%d, %d, %d)\n", i+1, j+1, mat[i][j]);
            }
        }
    }
}

int main() {
    int r, c;
    int mat1[MAX][MAX], mat2[MAX][MAX], result[MAX][MAX], transposed[MAX][MAX];

    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &r, &c);

    printf("Enter the first matrix:\n");
    inputMatrix(mat1, r, c);
    printMatrix(mat1, r, c);
    printTupleForm(mat1, r, c);

    printf("Enter the second matrix:\n");
    inputMatrix(mat2, r, c);
    printMatrix(mat2, r, c);
    printTupleForm(mat2, r, c);

    addMatrices(mat1, mat2, result, r, c);
    printf("Resultant matrix (sum of the two matrices):\n");
    printMatrix(result, r, c);
    printTupleForm(result, r, c);

    transposeMatrix(result, transposed, r, c);
    printf("Transpose of the resultant matrix:\n");
    printMatrix(transposed, c, r);
    printTupleForm(transposed, c, r);

    return 0;
}