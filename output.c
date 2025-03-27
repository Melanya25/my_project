#include "output.h"

void output_matrix_to_file(const Matrix* matrix, const char* filename) {
    if (!matrix) return;

    FILE* file = fopen(filename, "w");
    if (!file) return;

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            fprintf(file, "%lf\t", matrix->data[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}