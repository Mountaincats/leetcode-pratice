/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** restoreIpAddresses(char* s, int* returnSize) {
    int len = strlen(s);
    *returnSize = 0;

    char** ans = malloc(sizeof(char*) * 81);
    char* combine = malloc(sizeof(char) * (len + 3));
    int dot = 0, index = 0, num = 0, numSize = 0;

    void dfs(int size) {
        if (size == len + 3) {
            char* tmp = malloc(sizeof(char) * (len + 4));
            memcpy(tmp, combine, sizeof(char) * (len + 3));
            tmp[len + 3] = '\0';
            ans[(*returnSize)++] = tmp;
            return;
        }

        if (num != 0 && size < len + 2 && dot != 3) {
            combine[size] = '.';
            dot++;
            int tmp_num = num;
            int tmp_numSize = numSize;
            numSize = 0;
            num = 0;

            dfs(size + 1);
            dot--;
            numSize = tmp_numSize;
            num = tmp_num;
        }
        if (num != 3 && (num == 0 || numSize != 0) && (numSize * 10 + (s[index] - '0') < 256) && index < len) {
            combine[size] = s[index];
            num++;
            int tmp_numSize = numSize;
            numSize = numSize * 10 + (s[index++] - '0');
            
            dfs(size + 1);
            index--;
            numSize = tmp_numSize;
            num--;
        }
    }

    dfs(0);

    return ans;
}