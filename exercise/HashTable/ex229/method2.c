/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* majorityElement(int* nums, int numsSize, int* returnSize) {
    *returnSize = 0;
    int* ans = malloc(sizeof(int) * 2);
    int n = numsSize / 3;
    int element1 = 0;
    int element2 = 0;
    int vote1 = 0;
    int vote2 = 0;

    for (int i = 0; i < numsSize; i++) {
        if (vote1 > 0 && nums[i] == element1) {
            vote1++;
        }
        else if (vote2 > 0 && nums[i] == element2) {
            vote2++;
        }
        else if (vote1 == 0) {
            element1 = nums[i];
            vote1++;
        }
        else if (vote2 == 0) {
            element2 = nums[i];
            vote2++;
        }
        else {
            vote1--;
            vote2--;
        }
    }

    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < numsSize; i++) {
        if (vote1 > 0 && nums[i] == element1) {
            cnt1++;
        }
        if (vote2 > 0 && nums[i] == element2) {
            cnt2++;
        }
    }

    if (vote1 > 0 && cnt1 > n) {
        ans[(*returnSize)++] = element1;
    }
    if (vote2 > 0 && cnt2 > n) {
        ans[(*returnSize)++] = element2;
    }

    return ans;
}