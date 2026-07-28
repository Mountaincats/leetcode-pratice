bool canJump(int* nums, int numsSize) {
    int len = 1;
    for (int i = 0; i < len; i++) {
        len = fmax(len, i + nums[i] + 1);
        if (len >= numsSize) return true;
    }

    return false;
}