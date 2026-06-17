/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#define SUB_LEN 10

struct hashTable {
    char key[SUB_LEN + 1];
    int count;
    UT_hash_handle hh;
};

struct hashTable* hashtable;

struct hashTable* find(char* ikey) {
    struct hashTable* tmp;
    HASH_FIND_STR(hashtable, ikey, tmp);
    return tmp;
}

void insert(char* ikey) {
    struct hashTable* it = find(ikey);
    if (it == NULL) {
        struct hashTable* tmp = malloc(sizeof(struct hashTable));
        strncpy(tmp->key, ikey, SUB_LEN);
        tmp->key[SUB_LEN] = '\0';
        tmp->count = 1;
        HASH_ADD_STR(hashtable, key, tmp);
    } else {
        it->count += 1;
    }
}

void freehash() {
    struct hashTable *current, *tmp;
    HASH_ITER(hh, hashtable, current, tmp) {
        HASH_DEL(hashtable, current);
        free(current);
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

    int len = strlen(s);
    for (int i = 0; i <= len - SUB_LEN; i++) {
        char* sub = substring(s, i, SUB_LEN);
        insert(sub);
        if (find(sub)->count == 2) {
            ans[(*returnSize)++] = substring(s, i, SUB_LEN);
        }
        free(sub);
    }

    freehash();

    return ans;
}