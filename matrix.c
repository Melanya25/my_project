#include "matrix.h"

Matrix* matrix_create(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return NULL;

    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    if (!matrix) return NULL;

    matrix->data = (MatrixDataType**)malloc(rows * sizeof(MatrixDataType*));
    if (!matrix->data) {
        free(matrix);
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        matrix->data[i] = (MatrixDataType*)malloc(cols * sizeof(MatrixDataType));
        if (!matrix->data[i]) {
            // Clean up allocated memory if allocation fails
            for (int j = 0; j < i; j++) {
                free(matrix->data[j]);
            }
            free(matrix->data);
            free(matrix);
            return NULL;
        }
    }

    matrix->rows = rows;
    matrix->cols = cols;
    return matrix;
}

void matrix_free(Matrix* matrix) {
    if (!matrix) return;

    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

bool matrix_load_from_file(Matrix* matrix, const char* filename) {
    if (!matrix) return false;

    FILE* file = fopen(filename, "r");
    if (!file) return false;

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            if (fscanf(file, "%lf", &matrix->data[i][j]) != 1) {
                fclose(file);
                return false; // Error reading the file
            }
        }
    }

    fclose(file);
    return true;
}

void matrix_print(const Matrix* matrix) {
    if (!matrix) return;

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%lf\t", matrix->data[i][j]);
        }
        printf("\n");
    }
}

Matrix* matrix_copy(const Matrix* matrix) {
    if (!matrix) return NULL;

    Matrix* new_matrix = matrix_create(matrix->rows, matrix->cols);
    if (!new_matrix) return NULL;

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            new_matrix->data[i][j] = matrix->data[i][j];
        }
    }

    return new_matrix;
}

Matrix* matrix_add(const Matrix* matrix1, const Matrix* matrix2) {
    if (!matrix1 || !matrix2 || matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols) return NULL;

    Matrix* result = matrix_create(matrix1->rows, matrix1->cols);
    if (!result) return NULL;

    for (int i = 0; i < matrix1->rows; i++) {
        for (int j = 0; j < matrix1->cols; j++) {
            result->data[i][j] = matrix1->data[i][j] + matrix2->data[i][j];
        }
    }

    return result;
}

Matrix* matrix_multiply(const Matrix* matrix1, const Matrix* matrix2) {
    if (!matrix1 || !matrix2 || matrix1->cols != matrix2->rows) return NULL;

    Matrix* result = matrix_create(matrix1->rows, matrix2->cols);
    if (!result) return NULL;

    for (int i = 0; i < matrix1->rows; i++) {
        for (int j = 0; j < matrix2->cols; j++) {
            result->data[i][j] = 0;
            for (int k = 0; k < matrix1->cols; k++) {
                result->data[i][j] += matrix1->data[i][k] * matrix2->data[k][j];
            }
        }
    }

    return result;
}

Matrix* matrix_transpose(const Matrix* matrix) {
    if (!matrix) return NULL;

    Matrix* result = matrix_create(matrix->cols, matrix->rows);
    if (!result) return NULL;

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            result->data[j][i] = matrix->data[i][j];
        }
    }

    return result;
}

MatrixDataType matrix_determinant(const Matrix* matrix) {
     if (!matrix || matrix->rows != matrix->cols) {
        return 0.0; // Determinant is only defined for square matrices
    }

    int n = matrix->rows;

    if (n == 1) {
        return matrix->data[0][0];
    }

    if (n == 2) {
        return (matrix->data[0][0] * matrix->data[1][1] - matrix->data[0][1] * matrix->data[1][0]);
    }

    MatrixDataType det = 0.0;
    Matrix* submatrix = NULL;

    for (int i = 0; i < n; i++) {
        // Create a submatrix by excluding the first row and the i-th column
        submatrix = matrix_create(n - 1, n - 1);
        if (!submatrix) {
            // Handle allocation failure
            return 0.0; // Or some other error value
        }

        int sub_row = 0, sub_col = 0;
        for (int row = 1; row < n; row++) {
            sub_col = 0;
            for (int col = 0; col < n; col++) {
                if (col == i) continue; // Skip the i-th column

                submatrix->data[sub_row][sub_col] = matrix->data[row][col];
                sub_col++;
            }
            sub_row++;
        }

        // Calculate the determinant recursively and add to the total
        det += (i % 2 == 0 ? 1 : -1) * matrix->data[0][i] * matrix_determinant(submatrix);

        // Free the submatrix
        matrix_free(submatrix);
    }

    return det;
}