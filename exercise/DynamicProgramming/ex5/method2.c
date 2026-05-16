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
				// 奇回文中心
        int left = i - 1;
        int right = i + 1;
        int tmp_len = 1;
        while (left >= 0 && right < n) {
            if (s[left] == s[right]) {
                tmp_len += 2;
                left--;
                right++;
            }
            else break;
        }
        if (tmp_len > maxlen) {
            maxlen = tmp_len;
            begin = left + 1;
        }

				// 偶回文中心
				left = i;
				right = i + 1;
				tmp_len = 0;
				while (left >= 0 && right < n) {
						if (s[left] == s[right]) {
								tmp_len += 2;
								left--;
								right++;
						}
						else break;
				}
				if (tmp_len > maxlen) {
						maxlen = tmp_len;
						begin = left + 1;
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