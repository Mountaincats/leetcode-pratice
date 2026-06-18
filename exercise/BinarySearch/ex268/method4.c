int missingNumber(int* nums, int numsSize) {
    int arrsum = 0, sum = numsSize;
    for (int i = 0; i < numsSize; i++) {
        arrsum += nums[i];
        sum += i;
    }
    return sum - arrsum;
}