#include "testkit.h"

#ifndef TESTKIT_SOURCE_PATH
#error "TESTKIT_SOURCE_PATH must point to the source under test"
#endif
#include TESTKIT_SOURCE_PATH

enum {
    OP_SUM_RANGE = 0,
    OP_UPDATE = 1,
    OP_FIELD_COUNT = 4,
};

static void test_source(const TestCase *test_case) {
    int nums_size;
    int *nums = get_int_array(test_case, "nums", &nums_size);
    TestIntMatrix operations = get_int_matrix(test_case, "operations");
    int expected_result = 0;
    int actual_result = 0;
    bool result_mismatch = false;

    timer_start();
    NumArray *array = numArrayCreate(nums, nums_size);
    timer_stop();

    for (int i = 0; i < operations.row_count; i++) {
        int *operation = operations.rows[i];

        assert_int_equal(OP_FIELD_COUNT, operations.column_sizes[i]);
        if (operation[0] == OP_UPDATE) {
            timer_start();
            numArrayUpdate(array, operation[1], operation[2]);
            timer_stop();
        } else {
            int actual;

            assert_int_equal(OP_SUM_RANGE, operation[0]);
            timer_start();
            actual = numArraySumRange(array, operation[1], operation[2]);
            timer_stop();
            if (!result_mismatch && actual != operation[3]) {
                expected_result = operation[3];
                actual_result = actual;
                result_mismatch = true;
            }
        }
    }

    timer_start();
    numArrayFree(array);
    timer_stop();
    free(nums);
    free_int_matrix(&operations);

    if (result_mismatch) {
        assert_int_equal(expected_result, actual_result);
    }
}

int main(void) {
    return run_cases(TESTKIT_DATA_DIR, test_source);
}
