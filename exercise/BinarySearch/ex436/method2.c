/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct {
    int val;
    int index;
} Node;

int cmp(const void *a, const void *b) {
    return ((Node*)a)->val - ((Node*)b)->val;
}

int* findRightInterval(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize) {
    int* ans = malloc(sizeof(int) * intervalsSize);
    Node* start = malloc(sizeof(Node) * intervalsSize);
    Node* end = malloc(sizeof(Node) * intervalsSize);
    for (int i = 0; i < intervalsSize; i++) {
        start[i].index = i;
        end[i].index = i;
        start[i].val = intervals[i][0];
        end[i].val = intervals[i][1];
    }

    qsort(start, intervalsSize, sizeof(Node), cmp);
    qsort(end, intervalsSize, sizeof(Node), cmp);

    int left = 0, right = intervalsSize - 1;
    for (int i = 0; i < intervalsSize; i++) {
        while (left <= right) {
            int mid = (left + right) / 2;
            if (start[mid].val < end[i].val) left = mid + 1;
            else right = mid - 1;
        }
        ans[end[i].index] = left == intervalsSize ? -1 : start[left].index;
        right = intervalsSize - 1;
    }


    free(start);
    free(end);
    *returnSize = intervalsSize;
    return ans;
}