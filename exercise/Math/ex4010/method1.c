int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
    // if (a < b) {
    //     a ^= b ^= a ^= b;
    // }
    // while (true) {
    //     int q = a % b;
    //     if (q == 0) return b;
    //     else {
    //         a = b;
    //         b = q;
    //     }
    // }
}

int compare(const void* a, const void* b) {
    return *((int*)b) - *((int*)a);
}

long long maxPairStrength(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), compare);

    long long ans = 0;
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            long long mul = 1LL * nums[i] * nums[j];
            if (mul <= ans) break;
            long long g = gcd(nums[i], nums[j]);
            ans = fmax(ans, mul / (g * g));
        }
    }

    return ans;
}