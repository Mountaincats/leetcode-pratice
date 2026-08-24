typedef struct {
    int* sums;
} NumArray;

NumArray* numArrayCreate(int* nums, int numsSize) {
    NumArray* obj = malloc(sizeof(NumArray));
    obj->sums = malloc(sizeof(int) * (numsSize + 1));
    obj->sums[0] = 0;
    for (int i = 0, sum = 0; i < numsSize; i++) {
        sum += nums[i];
        obj->sums[i + 1] = sum;
    }

    return obj;
}

int numArraySumRange(NumArray* obj, int left, int right) {
    return obj->sums[right + 1] - obj->sums[left];
}

void numArrayFree(NumArray* obj) {
    free(obj->sums);
}

/**
 * Your NumArray struct will be instantiated and called as such:
 * NumArray* obj = numArrayCreate(nums, numsSize);
 * int param_1 = numArraySumRange(obj, left, right);
 
 * numArrayFree(obj);
*/