// This method may exceed time limit.
int minSubArrayLen(int target, int* nums, int numsSize) {
    int lenth = INT_MAX;

    for (int i = 0, sum = 0; i < numsSize; i++, sum = 0) {
        int sublen = 0;
        for (int j = i; j < numsSize; j++) {
            sum += nums[j];
            sublen++;
            if (sum >= target) {
                if (sublen < lenth) lenth = sublen;
                break;
            }
        }
    }

    return lenth == INT_MAX ? 0 : lenth;
}