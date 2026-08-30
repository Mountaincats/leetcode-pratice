#include "testkit.h"

#ifndef TESTKIT_SOURCE_PATH
#error "TESTKIT_SOURCE_PATH must point to the source under test"
#endif
#include TESTKIT_SOURCE_PATH

static void test_happy_number(const TestCase *test_case) {
    int n = get_int(test_case, "n");
    bool expected = get_bool(test_case, "expected");
    timer_start();
    bool actual = isHappy(n);
    timer_stop();
    assert_bool_equal(expected, actual);
}

int main(void) {
    return run_cases(TESTKIT_DATA_DIR, test_happy_number);
}
