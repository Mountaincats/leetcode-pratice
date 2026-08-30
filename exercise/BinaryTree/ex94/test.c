#include "testkit.h"

#ifndef TESTKIT_SOURCE_PATH
#error "TESTKIT_SOURCE_PATH must point to the source under test"
#endif
#include TESTKIT_SOURCE_PATH

static void test_inorder_traversal(const TestCase *test_case) {
    int expected_size;
    int actual_size = 0;
    struct TreeNode *root = get_tree(test_case, "root");
    int *expected = get_int_array(test_case, "expected", &expected_size);

    timer_start();
    int *actual = inorderTraversal(root, &actual_size);
    timer_stop();
    assert_array_equal(expected, expected_size, actual, actual_size);

    free(actual);
    free(expected);
    free_tree(root);
}

int main(void) {
    return run_cases(TESTKIT_DATA_DIR, test_inorder_traversal);
}
