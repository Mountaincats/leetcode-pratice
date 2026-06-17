/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#define SUB_LEN 10

int getHash(char input)
{   
    switch (input)
    {
        case 'A': return 0b00; break;
        case 'C': return 0b01; break;
        case 'G': return 0b10; break;
        case 'T': return 0b11; break;
        default:  return 0b00;break;
    }
}

char* substring(const char* str, int start, int len) {
    char* sub = malloc(sizeof(char) * (len + 1));
    if (sub == NULL) return NULL;

    strncpy(sub, str + start, len);
    sub[len] = '\0';
    return sub;
}

char** findRepeatedDnaSequences(char* s, int* returnSize) {
    // at most 100000 / 2 substrs appear at least 2 times
    char** ans = malloc(sizeof(char*) * 50000);
    *returnSize = 0;

    int hash = 0;
    int len = strlen(s);
    if (len < 10) return ans;

    for (int i = 0; i < SUB_LEN; i++) {
        hash = (hash << 2) | getHash(s[i]);
    }

    int* hashtable = malloc(sizeof(int) * (1 << 20));
    memset(hashtable, 0, sizeof(int) * (1 << 20));
    for (int i = 0; i <= len - SUB_LEN; i++) {
        hashtable[hash] += 1;
        if (hashtable[hash] == 2) ans[(*returnSize)++] = substring(s, i, SUB_LEN);
        hash = ((hash << 2) | getHash(s[i + SUB_LEN])) & ((1 << 20) - 1);
    }

    free(hashtable);

    return ans;
}