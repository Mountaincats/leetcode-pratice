int lengthOfLongestSubstring(char* s) {
    int start = 0, end = 0;
    int max = 0;
    bool index[128] = {false};
    int slen = strlen(s);

    for (; start < slen; index[s[start++]] = false) {
        while (end < slen && !index[s[end]]) {
            index[s[end++]] = true;
        }

        int len = end - start;
        max = (len > max) ? len : max;
    }

    return max;
}