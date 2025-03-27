#include "output.h"

//функция вывода матрицы из файла
void output_matrix_to_file(const Matrix* matrix, const char* file_name) {
    if (!matrix) return;

    FILE* file = fopen(file_name, "w"); //открытие файла для письма
    if (!file) return;

    //перебор элементов строк и столбцов матрицы
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            fprintf(file, "%lf\t", matrix->data[i][j]);
        }
        fprintf(file, "\n"); //вывод файла
    }

    fclose(file); //закрытие файла
}
