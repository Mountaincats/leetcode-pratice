/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

typedef struct hashTable{
    int val;
    int key;
    UT_hash_handle hh;
} hashTable;

struct hashTable* hashtable;

struct hashTable* find(int ikey) {
    struct hashTable* tmp;
    HASH_FIND_INT(hashtable, &ikey, tmp);
    return tmp;
}

void insert(int ikey) {
    struct hashTable* it = find(ikey);
    if(it == NULL) {
        struct hashTable* tmp = malloc(sizeof(struct hashTable));
        tmp->key = ikey, tmp->val = 1;
        HASH_ADD_INT(hashtable, key, tmp);
    }
    else {
        it->val += 1;
    }
}

int cmp(const hashTable* a, const hashTable* b) {
    return b->val - a->val;
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    int* ans = malloc(sizeof(int) * k);
    hashtable = NULL;

    for (int i = 0; i < numsSize; i++) {
        insert(nums[i]);
    }

    HASH_SORT(hashtable, cmp);
    struct hashTable *current = hashtable, *tmp;

    for (int i = 0; i < k && current != NULL; i++, current = current->hh.next) {
        ans[i] = current->key;
    }

    HASH_ITER(hh, hashtable, current, tmp) {
        HASH_DEL(hashtable, current);
        free(current);
    }

    *returnSize = k;
    return ans;
}