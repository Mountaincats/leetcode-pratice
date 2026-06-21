int arrayPairSum(int* nums, int numsSize) {
    int* cnt = calloc(20001, sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        cnt[nums[i] + 10000]++;
    }

    int* tmp = calloc(numsSize, sizeof(int));
    int index = 0;
    for (int i = 0; i < 20001; i++) {
        while (cnt[i]--) {
            tmp[index++] = i - 10000;
        }
    }

    int sum = 0;
    for (int i = 0; i < numsSize; i += 2) {
        sum += tmp[i];
    }

    free(cnt);
    free(tmp);
    return sum;
}