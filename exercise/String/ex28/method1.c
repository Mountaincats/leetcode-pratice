int strStr(char* haystack, char* needle) {
    int n = strlen(haystack);
    int m = strlen(needle);

    for (int i = 0; i <= n - m; i++) {
        bool find = true;
        for (int j = 0; j < m; j++) {
            if (needle[j] != haystack[i + j]) {
                find = false;
                break;
            }
        }
        if (find) return i;
    }
    return -1;
}