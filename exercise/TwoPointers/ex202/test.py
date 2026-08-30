from testkit import assert_equal, load_source_module, run_cases, timer_start, timer_stop


source_module = load_source_module()


def test_happy_number(test_case):
    implementation = source_module.Solution()
    n = test_case.get_int("n")
    expected = test_case.get_bool("expected")
    timer_start()
    actual = implementation.isHappy(n)
    timer_stop()
    assert_equal(expected, actual)


if __name__ == "__main__":
    raise SystemExit(run_cases(test_happy_number))
