#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char* longestPalindrome(char* s) {
    int n = strlen(s);
    if (n < 2) {
				char* result = malloc(2 * sizeof(char));
				result[0] = s[0];
				result[1] = '\0';

				return result;
		}

    int maxlen = 1;
    int begin = 0;
    
    for (int i = 0; i < n; i++) {
        int left = i - 1;
        int right = i + 1;
        int tmp = 1;
        while (left >= 0 && right < n) {
            if (s[left] == s[right]) {
                tmp += 2;
                left--;
                right++;
            }
            else break;
        }
        if (tmp > maxlen) {
            maxlen = tmp;
            begin = left + 1;
        }

        if (i < n - 1 && s[i] == s[i + 1]) {
            left = i - 1;
            right = i + 2;
            tmp = 2;
            while (left >= 0 && right < n) {
                if (s[left] == s[right]) {
                    tmp += 2;
                    left--;
                    right++;
                }
                else break;
            }
            if (tmp > maxlen) {
                maxlen = tmp;
                begin = left + 1;
            }
        }
    }

    char* result = (char*)malloc((maxlen + 1) * sizeof(char));
    
    if (result == NULL) {
        return NULL;
    }
    
    strncpy(result, s + begin, maxlen);
    result[maxlen] = '\0';
    
    return result;
}

int main() {
    char* s = (char*)malloc(1000 * sizeof(char));
    if (s == NULL) {
        return 1;
    }
    
    scanf("%s", s);
    char* g = longestPalindrome(s);
    printf("%s\n", g);

    free(g);
    free(s);

    return 0;
}