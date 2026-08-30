#include "testkit.h"

#ifndef TESTKIT_SOURCE_PATH
#error "TESTKIT_SOURCE_PATH must point to the source under test"
#endif
#include TESTKIT_SOURCE_PATH

static void test_valid_sudoku(const TestCase *test_case) {
    char storage[9][10];
    char *board[9];
    int column_sizes[9];

    for (int row = 0; row < 9; row++) {
        char key[8];
        const char *text;
        snprintf(key, sizeof(key), "row%d", row);
        text = get_string(test_case, key);
        memcpy(storage[row], text, 9);
        storage[row][9] = '\0';
        board[row] = storage[row];
        column_sizes[row] = 9;
    }

    bool expected = get_bool(test_case, "expected");
    timer_start();
    bool actual = isValidSudoku(board, 9, column_sizes);
    timer_stop();
    assert_bool_equal(expected, actual);
}

int main(void) {
    return run_cases(TESTKIT_DATA_DIR, test_valid_sudoku);
}
