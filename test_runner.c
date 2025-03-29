#include <CUnit/Basic.h>

// Declarations of test initialization functions from other test files
extern int tests_matrix_init(void);
extern int tests_matrix_cleanup(void);
extern int tests_output_init(void);
extern int tests_output_cleanup(void);

// Functions to add suites from other test files
extern CU_Suite* add_matrix_suite(void);
extern CU_Suite* add_output_suite(void);

int main() {
    // Initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    // Add suites from other test files
    CU_Suite* matrix_suite = add_matrix_suite();
    CU_Suite* output_suite = add_output_suite();

    if (!matrix_suite || !output_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

// --- Test Suite Definition Functions ---
// (These are needed because CUnit requires separate functions to add suites)

CU_Suite* add_matrix_suite(void) {
    CU_Suite* pSuite = CU_add_suite("Matrix Suite", tests_matrix_init, tests_matrix_cleanup);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return NULL;
    }

    // Add tests to the suite
    if ((NULL == CU_add_test(pSuite, "testCreateMatrix", testCreateMatrix)) ||
        (NULL == CU_add_test(pSuite, "testFreeMatrix", testFreeMatrix)) ||
        (NULL == CU_add_test(pSuite, "testAddMatrices", testAddMatrices)) ||
        (NULL == CU_add_test(pSuite, "testMultiplyMatrices", testMultiplyMatrices)) ||
        (NULL == CU_add_test(pSuite, "testTransposeMatrix", testTransposeMatrix)) ||
        (NULL == CU_add_test(pSuite, "testDeterminant", testDeterminant)) )
    {
        CU_cleanup_registry();
        return NULL;
    }

    return pSuite;
}

CU_Suite* add_output_suite(void) {
    CU_Suite* pSuite = CU_add_suite("Output Suite", tests_output_init, tests_output_cleanup);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return NULL;
    }

    // Add tests to the suite
    if ((NULL == CU_add_test(pSuite, "testWriteMatrixToFile", testWriteMatrixToFile)))
    {
        CU_cleanup_registry();
        return NULL;
    }

    return pSuite;
}

// --- Initialization and Cleanup Functions ---

int tests_matrix_init(void) { return 0; }
int tests_matrix_cleanup(void) { return 0; }
int tests_output_init(void) { return 0; }
int tests_output_cleanup(void) { return 0; }