/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

typedef struct hashTable{
    int val;
    int key;
    UT_hash_handle hh;
} hashTable;

typedef struct pair {
    int key;
    int val;
} pair;

struct hashTable* hashtable;
struct pair* heap;
int heapSize;

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

bool cmp(struct pair* a, struct pair* b) {
    return a->val < b->val;
}

void swap(pair* a, pair* b) {
    struct pair t = *a;
    *a = *b;
    *b = t;
}

struct pair top() {
    return heap[1];
}

void push(hashTable* obj) {
    heap[++heapSize].key = obj->key;
    heap[heapSize].val = obj->val;
    int child = heapSize, father;
    while (child > 1) {
        father = child >> 1;
        if (cmp(&heap[father], &heap[child])) return;
        swap(&heap[father], &heap[child]);
        child = father;
    }
}

void pop() {
    heap[1] = heap[heapSize--];
    int father = 1, child;
    while ((father << 1) <= heapSize) {
        child = father << 1;
        if (child < heapSize && cmp(&heap[child + 1], &heap[child])) child++;
        if (cmp(&heap[father], &heap[child])) return;
        swap(&heap[father], &heap[child]);
        father = child;
    }
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    int* ans = malloc(sizeof(int) * k);
    hashtable = NULL;

    for (int i = 0; i < numsSize; i++) {
        insert(nums[i]);
    }

    struct hashTable *current = NULL, *tmp = NULL;
    heap = malloc(sizeof(struct pair) * (k + 1));
    heapSize = 0;

    HASH_ITER(hh, hashtable, current, tmp) {
        if (heapSize == k) {
            struct pair tmp = top();
            if (tmp.val < current->val) {
                pop();
                push(current);
            }
        }
        else {
            push(current);
        }
    }

    for (int i = 1; i <= k; i++) {
        ans[i - 1] = heap[i].key;
    }

    HASH_ITER(hh, hashtable, current, tmp) {
        HASH_DEL(hashtable, current);
        free(current);
    }
    free(heap);

    *returnSize = k;
    return ans;
}