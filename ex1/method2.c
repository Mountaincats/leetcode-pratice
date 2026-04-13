// 哈希表

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct hashTable {
    int key;
    int val;
    UT_hash_handle hh;
};

struct hashTable* hashtable;

struct hashTable* find(int ikey) {
    struct hashTable* tmp;
    HASH_FIND_INT(hashtable, &ikey, tmp);
    return tmp;
}

void insert(int ikey, int ival) {
    struct hashTable* it = find(ikey);
    if(it == NULL) {
        struct hashTable* tmp = malloc(sizeof(struct hashTable));
        tmp->key = ikey, tmp->val = ival;
        HASH_ADD_INT(hashtable, key, tmp);
    }
    else {
        it->val = ival;
    }
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    hashtable = NULL;
    for(int i = 0; i < numsSize; i++){
        struct hashTable* it = find(target - nums[i]);
        if(it != NULL){
            int* ret = malloc(sizeof(int) * 2);
            ret[0] = it->val, ret[1] = i;
            *returnSize = 2;
            return ret;
        }
        insert(nums[i], i);
    }
    *returnSize = 0;

    // 修复：即使没有找到答案，也要清理哈希表
    struct hashTable *current, *tmp;
    HASH_ITER(hh, hashtable, current, tmp) {
        HASH_DEL(hashtable, current);
        free(current);
    }

    return NULL;
}
