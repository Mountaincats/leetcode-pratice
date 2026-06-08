/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void swap(int** a, int** b) {
    int* tmp = *a;
    *a = *b, *b = tmp;
}

int cmp(int* a, int* b) {
    return a[0] == b[0] ? a[1] - b[1] : a[0] - b[0];
}

struct Heap {
    int** heap;
    int size;
    int capacity;
};

int* top(struct Heap* obj) {
    return obj->heap[1];
}

void init(struct Heap* obj, int capacity) {
    obj->capacity = capacity;
    obj->size = 0;
    // 加1让索引从1开始
    obj->heap = malloc(sizeof(int*) * (capacity + 1));
    for (int i = 1; i <= obj->capacity; i++) {
        obj->heap[i] = malloc(sizeof(int) * 2);
    }
}

void setFree(struct Heap* obj) {
    for (int i = 1; i <= obj->capacity; i++) {
        free(obj->heap[i]);
    }
    free(obj->heap);
    free(obj);
}

void push(struct Heap* obj, int num, int index) {
    int child = ++(obj->size);
    int father = child >> 1;
    (obj->heap[child])[0] = num;
    (obj->heap[child])[1] = index;

    while (father > 0 && cmp(obj->heap[father], obj->heap[child]) < 0) {
        swap(&(obj->heap[father]), &(obj->heap[child]));
        child = father;
        father = child >> 1;
    }
}

void pop(struct Heap* obj) {
    int father = 1;
    swap(&(obj->heap[father]), &(obj->heap[(obj->size)--]));
    while (father <= obj->size) {
        int child1 = father << 1;
        int child2 = father << 1 | 1;
        int maxchild = father;

        if (child1 <= obj->size && cmp(obj->heap[maxchild], obj->heap[child1]) < 0) {
            maxchild = child1;
        }
        if (child2 <= obj->size && cmp(obj->heap[maxchild], obj->heap[child2]) < 0) {
            maxchild = child2;
        }
        if (father == maxchild) break;

        swap(&(obj->heap[father]), &(obj->heap[maxchild]));
        father = maxchild;
    }
}

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    int* ans = malloc(sizeof(int) * (numsSize - k + 1));
    *returnSize = 0;

    struct Heap* q = malloc(sizeof(struct Heap));
    init(q, numsSize);

    for (int i = 0; i < k; i++) {
        push(q, nums[i], i);
    }
    ans[(*returnSize)++] = top(q)[0];

    for (int i = k; i < numsSize; ++i) {
        push(q, nums[i], i);
        while (top(q)[1] <= i - k) {
            pop(q);
        }
        ans[(*returnSize)++] = top(q)[0];
    }

    setFree(q);
    return ans;
}