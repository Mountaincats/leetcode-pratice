int majorityElement(int* nums, int numsSize) {
    int element = nums[0];
    int num = 1;
    for (int i = 1; i < numsSize; i++) {
        if (num == 0) {
            num++;
            element = nums[i];
        }
        else if (nums[i] == element) {
            num++;
        }
        else {
            num--;
        }
    }

    // num = 0;
    // for (int i = 0; i < numsSize; i++) {
    //     if (nums[i] == element) num++;
    // }

    return element;
}