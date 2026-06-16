struct hashTable {
    int key;
    int count;
    UT_hash_handle hh;
};

struct hashTable* hashtable = NULL;

struct hashTable* find(int ikey) {
    struct hashTable* tmp;
    HASH_FIND_INT(hashtable, &ikey, tmp);
    return tmp;
}

void insert(int ikey) {
    struct hashTable* it = find(ikey);
    if (it == NULL) {
        struct hashTable* tmp = malloc(sizeof(struct hashTable));
        tmp->key = ikey;
        tmp->count = 1;
        HASH_ADD_INT(hashtable, key, tmp);
    } else {
        it->count += 1;
    }
}

void freehash(void) {
    struct hashTable *current, *tmp;
    HASH_ITER(hh, hashtable, current, tmp) {
        HASH_DEL(hashtable, current);
        free(current);
    }
}

int subarraySum(int* nums, int numsSize, int k) {
    int* sum = malloc(sizeof(int) * (numsSize + 1));
    sum[0] = 0;
    insert(sum[0]);
    int count = 0;

    for (int i = 0; i < numsSize; i++) {
        sum[i + 1] = sum[i] + nums[i];
        struct hashTable* tmp = find(sum[i + 1] - k);
        if (tmp != NULL) count += tmp->count;
        insert(sum[i + 1]);
    }

    free(sum);
    freehash();

    return count;
}