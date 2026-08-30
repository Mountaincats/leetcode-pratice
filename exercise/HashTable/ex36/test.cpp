#include "testkit.h"

#include <cstring>
#include <vector>

using namespace std;

#ifndef TESTKIT_SOURCE_PATH
#error "TESTKIT_SOURCE_PATH must point to the source under test"
#endif
#include TESTKIT_SOURCE_PATH

static void test_valid_sudoku(const TestCase *test_case) {
    vector<vector<char>> board;
    for (int row = 0; row < 9; row++) {
        char key[8];
        snprintf(key, sizeof(key), "row%d", row);
        const char *text = get_string(test_case, key);
        board.emplace_back(text, text + strlen(text));
    }

    Solution solution;
    timer_start();
    bool actual = solution.isValidSudoku(board);
    timer_stop();
    bool expected = get_bool(test_case, "expected");
    assert_bool_equal(expected, actual);
}

int main() {
    return run_cases(TESTKIT_DATA_DIR, test_valid_sudoku);
}
