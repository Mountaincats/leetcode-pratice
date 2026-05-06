int expand(const char* s, int left, int right, int n) {
    while (left >= 0 && right < n && s[left] == s[right]) {
        --left;
        ++right;
    }
    return (right - left - 2) / 2;
}

char* longestPalindrome(char* s) {
    int len = strlen(s);
    
    // 如果输入为空字符串，返回空字符串
    if (len == 0) {
        char* result = (char*)malloc(1);
        result[0] = '\0';
        return result;
    }
    
    // 构造新字符串，插入分隔符 '#'
    int t_len = 2 * len + 3;
    char* t = (char*)malloc(t_len + 1);
    t[0] = '#';
    for (int i = 0; i < len; ++i) {
        t[2 * i + 1] = s[i];
        t[2 * i + 2] = '#';
    }
    t[t_len - 1] = '\0';
    
    int* arm_len = (int*)malloc(t_len * sizeof(int));
    int right = -1, j = -1;
    int start = 0, end = -1;
    
    for (int i = 0; i < t_len - 1; ++i) {
        int cur_arm_len;
        if (right >= i) {
            int i_sym = 2 * j - i;
            int min_arm_len = arm_len[i_sym] < (right - i) ? arm_len[i_sym] : (right - i);
            cur_arm_len = expand(t, i - min_arm_len, i + min_arm_len, t_len);
        } else {
            cur_arm_len = expand(t, i, i, t_len);
        }
        
        arm_len[i] = cur_arm_len;
        
        if (i + cur_arm_len > right) {
            j = i;
            right = i + cur_arm_len;
        }
        
        if (cur_arm_len * 2 + 1 > end - start) {
            start = i - cur_arm_len;
            end = i + cur_arm_len;
        }
    }
    
    // 构造结果字符串
    int result_len = 0;
    for (int i = start; i <= end; ++i) {
        if (t[i] != '#') {
            ++result_len;
        }
    }
    
    char* result = (char*)malloc(result_len + 1);
    int idx = 0;
    for (int i = start; i <= end; ++i) {
        if (t[i] != '#') {
            result[idx++] = t[i];
        }
    }
    result[idx] = '\0';
    
    // 释放内存
    free(t);
    free(arm_len);
    
    return result;
}