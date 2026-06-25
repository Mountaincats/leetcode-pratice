int totalDigits(int length) {
    int digits = 0;
    int curlength = 1, curcount = 9;
    while (curlength <= length) {
        digits += curlength * curcount;
        curlength++;
        curcount *= 10;
    }
    return digits;
}

int findNthDigit(int n) {
    int low = 1, high = 9;
    while (low < high) {
        int mid = (low + high) / 2;
        if (totalDigits(mid) < n) {
            low = mid + 1;
        }
        else {
            high = mid;
        }
    }

    // 这个写法会运行 totalDigits(9) 进而导致溢出
    // while (low <= high) {
    //     int mid = (low + high) / 2;
    //     if (totalDigits(mid) < n) {
    //         low = mid + 1;
    //     }
    //     else {
    //         high = mid - 1;
    //     }
    // }

    int d = low;
    int prevDigits = totalDigits(d - 1);
    int index = n - prevDigits - 1;
    int start = (int)pow(10, d - 1);
    int num = start + index / d;

    int digitIndex = index % d;
    int digit = (num / (int)(pow(10, d - digitIndex - 1))) % 10;
    return digit;
}