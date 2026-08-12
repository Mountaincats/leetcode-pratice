int majorityElement(int* nums, int numsSize) {
    srand(time(NULL));
    while (true) {
        int element = nums[rand() % numsSize];
        int num = 0;
        for (int i = 0; i < numsSize; i++) {
            if (element == nums[i]) num++;
        }
        if (num > numsSize / 2) return element;
    }

    return -1;
}