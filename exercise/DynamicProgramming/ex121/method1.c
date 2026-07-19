#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

int maxProfit(int* prices, int pricesSize) {
    int minprice = prices[0], maxprofit = 0;
    for (int i = 1; i < pricesSize; i++) {
        minprice = min(minprice, prices[i]);
        maxprofit = max(maxprofit, prices[i] - minprice);
    }

    return maxprofit;
}