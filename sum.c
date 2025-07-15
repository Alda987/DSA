#include <stdio.h>

struct PolyTerm {
    int coef;
    int exp;
};

void inputPolynomial(struct PolyTerm poly[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and exponent of term %d: ", i + 1);
        scanf("%d %d", &poly[i].coef, &poly[i].exp);
    }
}

void displayPolynomial(struct PolyTerm poly[], int n) {
    for (int i = 0; i < n; i++) {
        if (poly[i].exp == 0)
            printf("%d", poly[i].coef);
        else
            printf("%d*x^%d", poly[i].coef, poly[i].exp);

        if (i != n - 1)
            printf(" + ");
    }
    printf("\n");
}


int addPolynomials(struct PolyTerm p1[], int n1, struct PolyTerm p2[], int n2, struct PolyTerm sum[]) {
    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2) {
        if (p1[i].exp > p2[j].exp) {
            sum[k++] = p1[i++];
        } else if (p1[i].exp < p2[j].exp) {
            sum[k++] = p2[j++];
        } else {
            sum[k].exp = p1[i].exp;
            sum[k].coef = p1[i].coef + p2[j].coef;
            i++; j++; k++;
        }
    }

   
    while (i < n1) {
        sum[k++] = p1[i++];
    }
    while (j < n2) {
        sum[k++] = p2[j++];
    }

    return k; 
}

int main() {
    int n1, n2, nsum;
    struct PolyTerm p1[10], p2[10], sum[20];

    printf("Enter number of terms in first polynomial: ");
    scanf("%d", &n1);
    inputPolynomial(p1, n1);

    printf("Enter number of terms in second polynomial: ");
    scanf("%d", &n2);
    inputPolynomial(p2, n2);

    nsum = addPolynomials(p1, n1, p2, n2, sum);

    printf("Sum of polynomials: ");
    displayPolynomial(sum, nsum);

    return 0;
}


