#include <stdio.h>
#include "matrix.h"
#include "output.h"

int main() {
    Matrix *A, *B, *C, *D, *result, *transposed_D;

    // Загрузка матриц из файлов
    A = matrix_create(2, 2);
    B = matrix_create(2, 2);
    C = matrix_create(2, 2);
    D = matrix_create(2, 2);

    //проверка условия
    if (!A || !B || !C || !D ||
        !matrix_load_from_file(A, "matrix_A.txt") ||
        !matrix_load_from_file(B, "matrix_B.txt") ||
        !matrix_load_from_file(C, "matrix_C.txt") ||
        !matrix_load_from_file(D, "matrix_D.txt")) {
        fprintf(stderr, "Error loading matrices from files.\n");
        return 1;
    }

    // Вычисление A * B - C + D^T
    Matrix* AB = matrix_multiply(A, B);
    transposed_D = matrix_transpose(D);
    Matrix* AB_minus_C = matrix_add(AB, matrix_multiply(C, matrix_create(2, 2)));
    result = matrix_add(AB_minus_C, transposed_D);

    //печать матрицы
    printf("Result Matrix:\n");
    matrix_print(result);

    // освобождение памяти
    matrix_free(A);
    matrix_free(B);
    matrix_free(C);
    matrix_free(D);
    matrix_free(AB);
    matrix_free(transposed_D);
    matrix_free(AB_minus_C);
    matrix_free(result);

    return 0;
}
