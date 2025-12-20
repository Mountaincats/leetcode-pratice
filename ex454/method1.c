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

void insert(int ikey) {
    struct hashTable* it = find(ikey);
    if(it == NULL) {
        struct hashTable* tmp = malloc(sizeof(struct hashTable));
        tmp->key = ikey, tmp->val = 1;
        HASH_ADD_INT(hashtable, key, tmp);
    }
    else {
        it->val = ++it->val;
    }
}

int fourSumCount(int* nums1, int nums1Size, int* nums2, int nums2Size, int* nums3, int nums3Size, int* nums4, int nums4Size) {
    hashtable = NULL;
    int ans = 0;

    for (int i = 0; i < nums1Size; i++) {
        for (int j = 0; j < nums1Size; j++) {
            insert(nums1[i] + nums2[j]);
        }
    }

    for (int i = 0; i < nums1Size; i++) {
        for (int j = 0; j < nums1Size; j++) {
            struct hashTable* tmp = find(-(nums3[i] + nums4[j]));
            if (tmp) ans += tmp->val; 
        }
    }

    return ans;
}