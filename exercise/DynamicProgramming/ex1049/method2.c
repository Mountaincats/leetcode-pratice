#define max(a, b) ((a) > (b) ? (a) : (b))

int lastStoneWeightII(int* stones, int stonesSize) {
    int sum = 0;
    for (int i = 0; i < stonesSize; i++) {
        sum += stones[i];
    }
    int target = sum / 2;  // 等价于一维 DP 的容量上限

    // 计算需要的 64 位字数量
    int words = (target + 64) / 64;
    uint64_t* bits = (uint64_t*)calloc(words, sizeof(uint64_t));
    uint64_t* shifted = (uint64_t*)calloc(words, sizeof(uint64_t));
    if (!bits || !shifted) {
        free(bits);
        free(shifted);
        return 0;
    }

    bits[0] = 1;  // 初始状态：重量为 0 可达

    for (int i = 0; i < stonesSize; i++) {
        int stone = stones[i];
        if (stone > target) continue;  // 剪枝：超过容量无意义

        memset(shifted, 0, words * sizeof(uint64_t));

        int word_shift = stone / 64;
        int bit_shift = stone % 64;

        // 遍历当前所有可达状态，生成加入当前石头后的新状态
        for (int j = 0; j < words - word_shift; j++) {
            if (bits[j] == 0) continue;

            int dest = j + word_shift;
            shifted[dest] |= bits[j] << bit_shift;

            // 处理跨字的高位溢出
            if (bit_shift && dest + 1 < words) {
                shifted[dest + 1] |= bits[j] >> (64 - bit_shift);
            }
        }

        // 合并状态：不选当前石头 OR 选当前石头
        for (int j = 0; j < words; j++) {
            bits[j] |= shifted[j];
        }
    }

    // 从 target 向下寻找最大的可达重量
    for (int j = target; j >= 0; j--) {
        int word_idx = j / 64;
        int bit_idx = j % 64;
        if ((bits[word_idx] >> bit_idx) & 1ULL) {
            free(bits);
            free(shifted);
            return sum - 2 * j;
        }
    }

    // 理论上不会走到这里
    free(bits);
    free(shifted);
    return sum;
}
