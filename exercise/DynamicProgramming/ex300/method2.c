int lengthOfLIS(int* nums, int numsSize) {
    int len = 1;
    int d[numsSize + 1];

    d[len] = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > d[len]) d[++len] = nums[i];
        else {
            int left = 1, right = len;
            while (left <= right) {
                int mid = (left + right) / 2;
                if (d[mid] < nums[i]) left = mid + 1;
                else right = mid - 1;
            }
            d[left] = nums[i];
        }
    }

    return len;
}