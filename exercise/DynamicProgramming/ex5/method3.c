int expand(const char* s, int left, int right, int n) {
    while (left >= 0 && right < n && s[left] == s[right]) {
        --left;
        ++right;
    }
    return (right - left - 2) / 2;
}

char* longestPalindrome(char* s) {
    int len = strlen(s);
    
    if (len == 0) {
        char* result = (char*)malloc(1);
        result[0] = '\0';
        return result;
    }
    
    // 构造新字符串，插入分隔符 '#'
    int t_len = 2 * len + 1;
    char* t = (char*)malloc(t_len + 1);
    t[0] = '#';
    for (int i = 0, j = 1; i < len; ++i, j += 2) {
        t[j] = s[i];
        t[j + 1] = '#';
    }
    t[t_len] = '\0';
    
		// 现有臂长
    int* arm_len = (int*)malloc(t_len * sizeof(int));
		// right 为现有臂长覆盖的最远距离， j 为其对应的回文中心
    int right = -1, j = -1;
		// 最长回文子串的边界
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
    int result_len = (end - start) / 2;
    
    char* result = (char*)malloc(result_len + 1);
    int idx = 0;
    for (int i = start + 1; i < end; i += 2) {
				result[idx++] = t[i];
    }
    result[idx] = '\0';
    
    free(t);
    free(arm_len);
    
    return result;
}