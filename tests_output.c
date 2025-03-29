#include <CUnit/Basic.h>
#include "output/output.h"
#include "matrix/matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_FILE "test_matrix_output.txt"

void test_Write_Matrix_To_File() {
    Matrix* matrix = create_Matrix(2, 2);
    matrix->data[0][0] = 1.0;
    matrix->data[0][1] = 2.0;
    matrix->data[1][0] = 3.0;
    matrix->data[1][1] = 4.0;

    bool result = write_Matrix_To_File(matrix, TEST_FILE);
    CU_ASSERT_TRUE(result);

    // Now, read the file back and verify its contents
    FILE* file = fopen(TEST_FILE, "r");
    CU_ASSERT_PTR_NOT_NULL(file);

    char buffer[100];
    fgets(buffer, sizeof(buffer), file);
    CU_ASSERT_STRING_EQUAL(buffer, "1.000000\t2.000000\t\n");
    fgets(buffer, sizeof(buffer), file);
    CU_ASSERT_STRING_EQUAL(buffer, "3.000000\t4.000000\t\n");

    fclose(file);
    remove(TEST_FILE); // Clean up the test file
    free_Matrix(matrix);
}