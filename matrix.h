#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "config.h"

//определяем структуру матрицы
typedef struct {
    Matrix_Data_Type **data;
    int rows;
    int cols;
} Matrix;

// Создание и освобождение
Matrix* matrix_create(int rows, int cols);
void matrix_free(Matrix* matrix);

// Ввод и вывод
bool matrix_load_from_file(Matrix* matrix, const char* filename);
void matrix_print(const Matrix* matrix);

// Операции копирования, сложения, умножения, транспонирования матриц и нахождения детерминанта
Matrix* matrix_copy(const Matrix* matrix);
Matrix* matrix_add(const Matrix* matrix1, const Matrix* matrix2);
Matrix* matrix_multiply(const Matrix* matrix1, const Matrix* matrix2);
Matrix* matrix_transpose(const Matrix* matrix);
MatrixDataType matrix_determinant(const Matrix* matrix);

#endif
