int strStr(char* haystack, char* needle) {
    int n = strlen(haystack);
    int m = strlen(needle);

    int* next = calloc(m, sizeof(int));

    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && needle[j] != needle[i]) j = next[j - 1];
        if (needle[j] == needle[i]) {
            next[i] = j + 1;
            j++;
        }
    }

    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && haystack[i] != needle[j]) j = next[j - 1];
        if (haystack[i] == needle[j]) {
            if (j == m - 1) {
                free(next);
                return i - m + 1;
            }
            j++;
        }
    }

    free(next);

    return -1;
}