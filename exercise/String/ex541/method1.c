void reverseString(char* s, int sSize) {
    for (int left = 0, right = sSize - 1; left < right; left++, right--) {
        s[left] = s[left] ^ s[right];
        s[right] = s[left] ^ s[right];
        s[left] = s[left] ^ s[right];
    }
}

char* reverseStr(char* s, int k) {
    int len = strlen(s);

    int left = 0, right = 0;
    while (1) {
        if (right + k <= len) reverseString(s + left, k);
        else {
            reverseString(s + left, len - right);
            return s;
        }
        
        if (right + 2 * k <= len) {
            left += 2 * k;
            right += 2 * k;
        }
        else return s;
    }
}