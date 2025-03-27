#include "matrix.h"

Matrix* matrix_create(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return NULL;

    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));//динамическое выделение памяти
    if (!matrix) return NULL; //проверка матрицы на нуль

    matrix->data = (Matrix_Data_Type**)malloc(rows * sizeof(Matrix_Data_Type*));
    if (!matrix->data) {
        free(matrix); //освобождение матрицы
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        //выделение памяти для указателя на матрицу
        matrix->data[i] = (Matrix_Data_Type*)malloc(cols * sizeof(Matrix_Data_Type));
        if (!matrix->data[i]) {
            //очистка памяти, нужной под файлы
            for (int j = 0; j < i; j++) {
                free(matrix->data[j]); //освобождение указателя на элементы матрицы
            }
            //освобождение указателя и самой матрицы
            free(matrix->data);
            free(matrix);
            return NULL;
        }
    }
    
    matrix->rows = rows;
    matrix->cols = cols;
    return matrix; //возвращение матрицы
}
//функция освобождения матрицы
void matrix_free(Matrix* matrix) {
    if (!matrix) return;

    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]); //освобождение указателя на элементы матрицы
    } 
    //освобождение указателя на матрицу и самой матрицы
    free(matrix->data);
    free(matrix);
}
//функция загрузки матриц из файлов
bool matrix_load_from_file(Matrix* matrix, const char* file_name) {
    if (!matrix) return false;

    FILE* file = fopen(file_name, "r");
    if (!file) return false;
    //перебор элементов матрицы
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            if (fscanf(file, "%lf", &matrix->data[i][j]) != 1) {
                fclose(file); //закрытие файла
                return false; // ошибка чтения файла
            }
        }
    }

    fclose(file); //закрытие файла
    return true;
}
//функция печати матрицы
void matrix_print(const Matrix* matrix) {
    if (!matrix) return;
    //перебор элементов матрицы
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%lf\t", matrix->data[i][j]);
        }
        printf("\n");
    }
}
//функция копирования матрицы
Matrix* matrix_copy(const Matrix* matrix) {
    if (!matrix) return NULL;

    Matrix* new_matrix = matrix_create(matrix->rows, matrix->cols); //создание новой матрицы
    if (!new_matrix) return NULL;

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            new_matrix->data[i][j] = matrix->data[i][j]; //указатель на новую матрицу равен указателю на исходную матрицу
        }
    }

    return new_matrix; //возвращаем новую матрицу
}
//функция сложения матриц
Matrix* matrix_add(const Matrix* matrix_1, const Matrix* matrix_2) {
    if (!matrix_1 || !matrix_2 || matrix_1->rows != matrix_2->rows || matrix_1->cols != matrix_2->cols) return NULL;

    Matrix* result = matrix_create(matrix_1->rows, matrix_1->cols); //создание результирующего значения
    if (!result) return NULL;

    for (int i = 0; i < matrix_1->rows; i++) {
        for (int j = 0; j < matrix_1->cols; j++) {
            result->data[i][j] = matrix_1->data[i][j] + matrix_2->data[i][j]; //сложение элементов матриц
        }
    }

    return result; //возвращение результирующего значения
}
//функция умножения матриц
Matrix* matrix_multiply(const Matrix* matrix_1, const Matrix* matrix_2) {
    if (!matrix_1 || !matrix_2 || matrix_1->cols != matrix_2->rows) return NULL;

    Matrix* result = matrix_create(matrix_1->rows, matrix_2->cols); //создание результирующего значения
    if (!result) return NULL; //проверка на нуль

    for (int i = 0; i < matrix_1->rows; i++) {
        for (int j = 0; j < matrix_2->cols; j++) {
            result->data[i][j] = 0; //инициализация указателя на результирующее значение
            for (int k = 0; k < matrix_1->cols; k++) {
                result->data[i][j] += matrix_1->data[i][k] * matrix_2->data[k][j]; //умножение элементов матриц
            }
        }
    }

    return result; //возвращение результирующего значения
}
//функция транспонирования матриц
Matrix* matrix_transpose(const Matrix* matrix) {
    if (!matrix) return NULL;

    Matrix* result = matrix_create(matrix->cols, matrix->rows);
    if (!result) return NULL; //проверка результирующего значения на нуль

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            result->data[j][i] = matrix->data[i][j]; //транспонирование матрицы
        }
    }

    return result;
}
//функция нахождения детерминанта матрицы
Matrix_Data_Type matrix_determinant(const Matrix* matrix) {
     if (!matrix || matrix->rows != matrix->cols) {
        return 0.0; //обнуление детерминанта
    }

    int n = matrix->rows; 
    
    //для матрицы 1 на 1
    if (n == 1) {
        return matrix->data[0][0];
    }
    //для матрицы 2 на 2
    if (n == 2) {
        return (matrix->data[0][0] * matrix->data[1][1] - matrix->data[0][1] * matrix->data[1][0]);
    }
    //для произвольной матрицы
    Matrix_Data_Type det = 0.0;
    Matrix* sub_matrix = NULL;

    for (int i = 0; i < n; i++) {
        // Create a sub_matrix by excluding the first row and the i-th column
        sub_matrix = matrix_create(n - 1, n - 1);
        if (!sub_matrix) {
            return 0.0;
        }
        //инициализация строк и столбцов
        int sub_row = 0, sub_col = 0;
        for (int row = 1; row < n; row++) {
            sub_col = 0; //инициализируем столбцы в нуль
            for (int col = 0; col < n; col++) {
                if (col == i) continue; 

                sub_matrix->data[sub_row][sub_col] = matrix->data[row][col];
                sub_col++; //увеличиваем количество столбцов
            }
            sub_row++; //увеличиваем количество строк
        }

        // Calculate the determinant recursively and add to the total
        det += (i % 2 == 0 ? 1 : -1) * matrix->data[0][i] * matrix_determinant(sub_matrix);

        // Free the sub_matrix
        matrix_free(sub_matrix);
    }

    return det; //возвращаем значение детерминанта
}
