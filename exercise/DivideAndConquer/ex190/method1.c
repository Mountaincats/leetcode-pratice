int reverseBits(int n) {
    uint32_t ans = 0;
    uint32_t N = n;
    for (int i = 0; i < 32 && N > 0; i++) {
        ans |= (N & 1) << (31 - i);
        N >>= 1;
    }

    return ans;
}