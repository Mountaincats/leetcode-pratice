int missingNumber(int* nums, int numsSize) {
    int* set = calloc(numsSize + 1, sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        set[nums[i]] = 1;
    }
    for (int i = 0; i <= numsSize; i++) {
        if (set[i] == 0) return i;
    }
    
		free(set);

    return 0;
}