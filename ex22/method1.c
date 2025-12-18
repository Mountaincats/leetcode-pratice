/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

char* combination;
int combination_size;

char** combinations;
int combinations_size;

int n_size;

int left = 1;
int right = 0;

char parenthesis[] = {'(', ')'};

void backtrack(int index) {
    if (index == 2 * n_size - 1) {
        combination[n_size * 2 - 1] = ')';
        combination[n_size * 2] = 0; //字符串不会被自动初始化为/0

        char* tmp = (char*)malloc((n_size * 2 + 1) * sizeof(char));
        memcpy(tmp, combination, (n_size * 2 + 1) * sizeof(char));
        combinations[combinations_size++] = tmp;
    }
    else {
        for (int i = 0; i < 2; i++) {
            combination[combination_size++] = parenthesis[i];

            if (i) right++;
            else left++;

            if (right > left) {
                right--;
                combination_size--;
                continue;
            }
            else if (left > n_size) {
                left--;
                combination_size--;
                continue;
            }

            backtrack(index + 1);
            combination[--combination_size] = 0;
            if (i) right--;
            else left--;
        }
    }
}

char** generateParenthesis(int n, int* returnSize) {
    n_size = n;
    combination_size = 1;
    combinations_size = 0;

    int num = 1;
    for (int i = 0; i < n - 1; i++) num *= 4;
    combination = (char*)malloc((n_size * 2 + 1) * sizeof(char));
    combinations = (char**)malloc(num * sizeof(char*));

    combination[0] = '(';
    backtrack(1);

    *returnSize = combinations_size;
    return combinations;
}