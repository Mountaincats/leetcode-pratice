#include<stdio.h>
#include<stdbool.h>
#include<string.h>

bool isAnagram(char* s, char* t) {
    int letter[26] = {0}; //如果设为全局变量,在多次调用之间会保留之前的值。LeetCode 的测试框架会多次调用同一个函数，可能导致后续测试失败

    if (strlen(s) != strlen(t)) return false;

    for (int i = 0; i < strlen(s); i++){
        letter[s[i] - 'a']++;
        letter[t[i] - 'a']--;
    }
    for (int i = 0; i < sizeof(letter)/sizeof(letter[0]); i++) {
        if (letter[i] != 0) return false;
    }

    return true;
}

int main() {
    if (isAnagram("a", "a")) printf("Is anagram\n");
    else printf("Is not anagram\n");

    return 0;
}