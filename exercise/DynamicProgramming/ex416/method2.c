#define max(a, b) ((a) > (b) ? (a) : (b))

bool canPartition(int* nums, int numsSize) {
    if (numsSize < 2) return false;
    
    int sum = nums[0], maxNum = nums[0];
    for (int i = 1; i < numsSize; i++) {
        sum += nums[i];
        maxNum = max(nums[i], maxNum);
    }

    if (sum & 1) return false;
    int target = sum >> 1;
    if (maxNum > target) return false;

    // 计算要多少个 64 位数据
    int words = (target + 64) / 64;
    // bits 等价 dp[target + 1]
    uint64_t* bits = (uint64_t*)calloc(words, sizeof(uint64_t));
    uint64_t* shifted = (uint64_t*)calloc(words, sizeof(uint64_t));
    if (!bits || !shifted) {
        free(bits); free(shifted);
        return false;
    }

    bits[0] = 1;

    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        // 剪枝：如果数字为 0 或大于目标值，直接跳过
        if (num > target || num == 0) continue;

        // 清空临时数组，用于存放 "选了当前数字" 后的新状态
        memset(shifted, 0, words * sizeof(uint64_t));
        
        // 将位移量拆分为：跨多少个 64 位字 + 剩余多少位
        int word_shift = num / 64;
        int bit_shift = num % 64;

        // 遍历当前所有可达的状态（bits 数组）
        // j < words - word_shift 防止写入越界
        for (int j = 0; j < words - word_shift; j++) {
            // 如果该 64 位字中没有可达状态，跳过以加速
            if (bits[j] == 0) continue;
            
            // 计算当前状态要写入的目标字索引
            int dest = j + word_shift;
            
            // 核心位移（低位部分）：
            // 将当前字的状态左移 bit_shift 位，存入目标字
            shifted[dest] |= bits[j] << bit_shift;
            
            // 核心位移（高位进位）：
            // 如果位移不是 64 的整数倍，低位字的高位会溢出到下一个字
            if (bit_shift && dest + 1 < words) {
                // 将溢出的高位拼接到下一个字的低位
                shifted[dest + 1] |= bits[j] >> (64 - bit_shift);
            }
        }

        // 状态合并：将新产生的状态（shifted）合并回主状态集（bits）
        // bits | shifted 等价于 "不选当前数" OR "选了当前数"
        for (int j = 0; j < words; j++) {
            bits[j] |= shifted[j];
        }
    }

    // 等价 method1 获取 dp[target]
    int target_word = target / 64;
    int target_bit = target % 64;
    bool result = (bits[target_word] >> target_bit) & 1;
    
    free(bits);
    free(shifted);
    return result;
}