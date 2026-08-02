int compare(const void* a, const void* b) {
    return (*(int**)a)[1] - (*(int**)b)[1];
}

int eraseOverlapIntervals(int** intervals, int intervalsSize, int* intervalsColSize) {
    qsort(intervals, intervalsSize, sizeof(int*), compare);

    int ans = 0;

    int pre_end = intervals[0][1];
    for (int i = 1; i < intervalsSize; i++) {
        if (intervals[i][1] > pre_end) {
            if (intervals[i][0] < pre_end) ans++;
            else pre_end = intervals[i][1];
        }
        else ans++;
    }

    return ans;
}