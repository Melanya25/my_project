#include <stdio.h>
#include "matrix.h"
#include "output.h"

int main() {
    Matrix *A, *B, *C, *D, *result, *transposedD;

    // Load matrices from files
    A = matrix_create(2, 2);
    B = matrix_create(2, 2);
    C = matrix_create(2, 2);
    D = matrix_create(2, 2);

    if (!A || !B || !C || !D ||
        !matrix_load_from_file(A, "matrix_A.txt") ||
        !matrix_load_from_file(B, "matrix_B.txt") ||
        !matrix_load_from_file(C, "matrix_C.txt") ||
        !matrix_load_from_file(D, "matrix_D.txt")) {
        fprintf(stderr, "Error loading matrices from files.\n");
        return 1;
    }

    // Calculate A * B - C + D^T
    Matrix* AB = matrix_multiply(A, B);
    transposedD = matrix_transpose(D);
    Matrix* AB_minus_C = matrix_add(AB, matrix_multiply(C, matrix_create(2, 2)));
    result = matrix_add(AB_minus_C, transposedD);

    printf("Result Matrix:\n");
    matrix_print(result);

    // Clean up
    matrix_free(A);
    matrix_free(B);
    matrix_free(C);
    matrix_free(D);
    matrix_free(AB);
    matrix_free(transposedD);
    matrix_free(AB_minus_C);
    matrix_free(result);

    return 0;
}