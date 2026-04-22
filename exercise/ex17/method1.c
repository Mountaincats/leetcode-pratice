/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** letterCombinations(char* digits, int* returnSize) {
    char* p[] = {
        "abc",  "def", "ghi", "jkl",
        "mno", "pqrs", "tuv", "wxyz"  // 索引2-9对应数字2-9
    };

    int num_block = 1;

    for (int i = 0; i < strlen(digits); i++) {
        if (digits[i] - '0' == 7 || digits[i] - '0' == 9) {
            num_block *= 4;
        }
        else num_block *= 3;
    }

    *returnSize = num_block;
    int size_block = 1;
    int repeat = 1;

    // 1. 分配结果指针数组
    char** out = (char**)malloc(num_block * sizeof(char*));
    
    // 2. 为结果中的每一个字符串分配内存
    for (int i = 0; i < num_block; i++) {
        out[i] = (char*)malloc((strlen(digits) + 1) * sizeof(char)); // +1 用于存放字符串结束符 '\0'
        out[i][strlen(digits)] = '\0'; // 设置字符串结束符
    }

    for (int i = strlen(digits) - 1; i >= 0; i--) {
        int num = strlen(p[digits[i] - '2']);
        num_block /= num;
        size_block *= num;

        for (int j = 0; j < num_block; j++) {
            for (int k = 0; k < num; k++) {
                for (int l = 0; l < repeat; l++) {
                    out[j * size_block + k * repeat + l][i] = p[digits[i] - '2'][k];
                }
            }
        }

        repeat *= num;
    }

    return out;
}