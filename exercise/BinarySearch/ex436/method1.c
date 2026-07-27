/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct {
    int start;
    int index;
} Node;

int cmp(const void *a, const void *b) {
    return ((Node*)a)->start - ((Node*)b)->start;
}

int* findRightInterval(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize) {
    int* ans = malloc(sizeof(int) * intervalsSize);
    Node* tmp = malloc(sizeof(Node) * intervalsSize);
    for (int i = 0; i < intervalsSize; i++) {
        tmp[i].index = i;
        tmp[i].start = intervals[i][0];
    }

    qsort(tmp, intervalsSize, sizeof(Node), cmp);

    for (int i = 0; i < intervalsSize; i++) {
        int left = 0, right = intervalsSize - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (tmp[mid].start < intervals[i][1]) left = mid + 1;
            else right = mid - 1;
        }
        ans[i] = left == intervalsSize ? -1 : tmp[left].index;
    }


    free(tmp);
    *returnSize = intervalsSize;
    return ans;
}