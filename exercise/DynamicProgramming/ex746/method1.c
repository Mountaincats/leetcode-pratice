#define min(a, b) ((a) < (b) ? (a) : (b))

int minCostClimbingStairs(int* cost, int costSize) {
    int p = 0, q = 0;
    for (int i = 2; i <= costSize ; i++) {
        p = min(p + cost[i - 2], q + cost[i - 1]);

        p = p ^ q;
        q = p ^ q;
        p = p ^ q;
    }

    return q;
}