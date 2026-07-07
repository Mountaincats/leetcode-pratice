/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

struct hashTable {
    int key;
    int val;
    UT_hash_handle hh;
};

struct hashTable* hashtable;

struct hashTable* find(int key) {
    struct hashTable* tmp;
    HASH_FIND_INT(hashtable, &key, tmp);
    return tmp;
}

void insert(int key) {
    struct hashTable* tmp = find(key);
    if (tmp != NULL) {
        tmp->val++;
    }
    else {
        tmp = malloc(sizeof(struct hashTable));
        tmp->key = key;
        tmp->val = 1;
        HASH_ADD_INT(hashtable, key, tmp);
    }
}

int* majorityElement(int* nums, int numsSize, int* returnSize) {
    hashtable = NULL;
    int n = numsSize / 3;
    for (int i = 0; i < numsSize; i++) {
        insert(nums[i]);
    }

    int* ans = malloc(sizeof(int) * 2);
    *returnSize = 0;

    struct hashTable *cur, *tmp;
    HASH_ITER(hh, hashtable, cur, tmp) {
        if (cur->val > n) {
            ans[(*returnSize)++] = cur->key;
        }
        HASH_DEL(hashtable, cur);
        free(cur);
    }

    return ans;
}