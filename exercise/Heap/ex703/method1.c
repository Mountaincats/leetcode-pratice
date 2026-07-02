struct Heap {
    int* heap;
    int heapSize;
    bool (*cmp)(int, int);
};

bool cmp(int a, int b) {
    return a > b;
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void init(struct Heap* obj, int n, bool (*cmp)(int, int)) {
    // 索引从 1 开始
    obj->heap = malloc(sizeof(int) * (n + 1));
    obj->heapSize = 0;
    obj->cmp = cmp;
}

void push(struct Heap* obj, int val) {
    int child = ++(obj->heapSize), father = child >> 1;
    obj->heap[child] = val;
    while (father) {
        if (obj->cmp(obj->heap[child], obj->heap[father])) {
            break;
        }
        swap(&(obj->heap[child]), &(obj->heap[father]));
        child = father;
        father = child >> 1;
    }
}

void pop(struct Heap* obj) {
    obj->heap[1] = obj->heap[(obj->heapSize)--];
    int father = 1, child = father << 1;
    while (child <= obj->heapSize) {
        if (child + 1 <= obj->heapSize && obj->cmp(obj->heap[child], obj->heap[child + 1])) child++;
        if (obj->cmp(obj->heap[child], obj->heap[father])) break;
        swap(&(obj->heap[child]), &(obj->heap[father]));
        father = child;
        child = father << 1;
    }
}

int top(struct Heap* obj) {
    return obj->heap[1];
}

typedef struct {
    struct Heap* heap;
    int maxSize;
} KthLargest;

int kthLargestAdd(KthLargest* obj, int val) {
    if (obj->heap->heapSize != obj->maxSize) push(obj->heap, val);
    else if (top(obj->heap) < val) {
        pop(obj->heap);
        push(obj->heap, val);
    }
    return top(obj->heap);
}

KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
    KthLargest* ret = malloc(sizeof(KthLargest));
    ret->heap = malloc(sizeof(struct Heap));
    init(ret->heap, k, cmp);
    ret->maxSize = k;
    for (int i = 0; i < numsSize; i++) {
        kthLargestAdd(ret, nums[i]);
    }

    return ret;
}

void kthLargestFree(KthLargest* obj) {
    free(obj->heap->heap);
    free(obj->heap);
    free(obj);
}

/**
 * Your KthLargest struct will be instantiated and called as such:
 * KthLargest* obj = kthLargestCreate(k, nums, numsSize);
 * int param_1 = kthLargestAdd(obj, val);
 
 * kthLargestFree(obj);
*/