int compare(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int findContentChildren(int* g, int gSize, int* s, int sSize) {
    int smallest_s = 0;
    int smallest_g = 0;
    int content_g = 0;

    qsort(s, sSize, sizeof(int), compare);
    qsort(g, gSize, sizeof(int), compare);

    for (; smallest_s < sSize && smallest_g < gSize; smallest_s++) {
        if(s[smallest_s] >= g[smallest_g]) {
            content_g++;
            smallest_g++;
        }
    }

    return content_g;
}