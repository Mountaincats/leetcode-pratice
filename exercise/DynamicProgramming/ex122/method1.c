#define max(a, b) ((a) > (b) ? (a) : (b))

int maxProfit(int* prices, int pricesSize) {
    int p = 0, q = -prices[0];
    for (int i = 0; i < pricesSize; i++) {
        int next_p = max(p, q + prices[i]);
        int next_q = max(q, p - prices[i]);
        p = next_p;
        q = next_q;
    }

    return p;
}