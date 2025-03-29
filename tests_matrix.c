#include <CUnit/Basic.h>
#include "matrix/matrix.h"

// Сравнивает две матрицы на равенство с учетом заданной погрешности для чисел с плавающей точкой.
bool matrices_Equal(const Matrix* a, const Matrix* b, double tolerance) {
    if (a == NULL && b == NULL) return true; // Оба NULL - считаем равными.
    if (a == NULL || b == NULL) return false; // Один из них NULL, а другой нет - не равны.

    if (a->rows != b->rows || a->cols != b->cols) return false; // Размеры не совпадают - не равны.

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            // Проверяем, что разница между элементами не превышает заданную погрешность.
            if (fabs(a->data[i][j] - b->data[i][j]) > tolerance) return false;
        }
    }

    return true; // Все проверки пройдены - матрицы равны.
}
// Проверяет, что функция создает матрицу с заданными размерами и выделяет для нее память.
void test_Create_Matrix() {
    Matrix* matrix = create_Matrix(2, 3);  // Создаем матрицу 2x3.
    CU_ASSERT_PTR_NOT_NULL(matrix);
    CU_ASSERT_EQUAL(matrix->rows, 2);
    CU_ASSERT_EQUAL(matrix->cols, 3);
    free_Matrix(matrix); // Освобождаем память, выделенную для матрицы.
}
// Проверяет, что функция освобождает память, выделенную для матрицы.
void test_Free_Matrix() {
    Matrix* matrix = create_Matrix(2, 3);
    free_Matrix(matrix); 
}
// Проверяет, что функция правильно складывает две матрицы.
void test_Add_Matrices() {
    Matrix* matrix_1 = create_Matrix(2, 2);
    Matrix* matrix_2 = create_Matrix(2, 2);

     // Заполняем матрицы данными.
    matrix_1->data[0][0] = 1; matrix_1->data[0][1] = 2; matrix_1->data[1][0] = 3; matrix_1->data[1][1] = 4;
    matrix_2->data[0][0] = 5; matrix_2->data[0][1] = 6; matrix_2->data[1][0] = 7; matrix_2->data[1][1] = 8;

    Matrix* sum = add_Matrices(matrix_1, matrix_2); // Складываем матрицы.
    CU_ASSERT_PTR_NOT_NULL(sum); // Проверяем, что указатель на сумму не NULL 
    CU_ASSERT_EQUAL(sum->data[0][0], 6);
    CU_ASSERT_EQUAL(sum->data[0][1], 8);
    CU_ASSERT_EQUAL(sum->data[1][0], 10);
    CU_ASSERT_EQUAL(sum->data[1][1], 12);
    
    // Освобождаем память
    free_Matrix(matrix_1);
    free_Matrix(matrix_2);
    free_Matrix(sum);
}
// Тест для функции multiply_Matrices
void test_Multiply_Matrices() {
    Matrix* matrix_1 = create_Matrix(2, 2);
    Matrix* matrix_2 = create_Matrix(2, 2);

    // Заполняем матрицы данными.
    matrix_1->data[0][0] = 1; matrix_1->data[0][1] = 2; matrix_1->data[1][0] = 3; matrix_1->data[1][1] = 4;
    matrix_2->data[0][0] = 5; matrix_2->data[0][1] = 6; matrix_2->data[1][0] = 7; matrix_2->data[1][1] = 8;

    Matrix* product = multiply_Matrices(matrix_1, matrix_2); // Умножаем матрицы
    CU_ASSERT_PTR_NOT_NULL(product);
    CU_ASSERT_EQUAL(product->data[0][0], 19);
    CU_ASSERT_EQUAL(product->data[0][1], 22);
    CU_ASSERT_EQUAL(product->data[1][0], 43);
    CU_ASSERT_EQUAL(product->data[1][1], 50);
    
    // Освобождаем память
    free_Matrix(matrix_1);
    free_Matrix(matrix_2);
    free_Matrix(product);
}

void test_Transpose_Matrix() {
    // Тест для функции transpose_Matrix 
    Matrix* matrix = create_Matrix(2, 3); // Создаем матрицу 2x3.

    // Заполняем матрицу данными.
    matrix->data[0][0] = 1; 
    matrix->data[0][1] = 2;
    matrix->data[0][2] = 3;
    matrix->data[1][0] = 4; 
    matrix->data[1][1] = 5; 
    matrix->data[1][2] = 6;
    
    // Транспонируем матрицу.
    Matrix* transposed = transpose_Matrix(matrix);
    CU_ASSERT_PTR_NOT_NULL(transposed);
    CU_ASSERT_EQUAL(transposed->rows, 3);
    CU_ASSERT_EQUAL(transposed->cols, 2);
    CU_ASSERT_EQUAL(transposed->data[0][0], 1);
    CU_ASSERT_EQUAL(transposed->data[0][1], 4);
    CU_ASSERT_EQUAL(transposed->data[1][0], 2);
    CU_ASSERT_EQUAL(transposed->data[1][1], 5);
    CU_ASSERT_EQUAL(transposed->data[2][0], 3);
    CU_ASSERT_EQUAL(transposed->data[2][1], 6);
    
    // Освобождаем память
    free_Matrix(matrix);
    free_Matrix(transposed);
}

// Тест для функции determinant 
void test_Determinant() {
    Matrix* matrix = create_Matrix(3, 3); // Создаем матрицу 3x3.
    matrix->data[0][0] = 1; matrix->data[0][1] = 2; matrix->data[0][2] = 3;
    matrix->data[1][0] = 4; matrix->data[1][1] = 5; matrix->data[1][2] = 6;
    matrix->data[2][0] = 7; matrix->data[2][1] = 8; matrix->data[2][2] = 9;

    double det = determinant(matrix);
   CU_ASSERT(double_equals(det, 0.0, 1e-6)); // Проверяем, что детерминант равен 0.0

    free_Matrix(matrix); // Освобождаем память, выделенную для матрицы.
}
