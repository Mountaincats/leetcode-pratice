int jump(int* nums, int numsSize) {
    int step = 0;
    int len = 1;
    int start = 0;

    while (len < numsSize) {
        step++;
        int next_len = len;
        for (; start < len; start++) {
            next_len = fmax(next_len, start + nums[start] + 1);
        }
        len = next_len;
    }

    return step;
}
