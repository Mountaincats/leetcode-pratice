char* removeDuplicates(char* s, int k) {
    char* stack = malloc(sizeof(char) * strlen(s) + 1);
    int top = -1;
    bool kflag = true;
    char* begin = s;

    while (kflag) {
        kflag = false;
        int count = 0;
        while (*begin != '\0') {
            if (top == -1) {
                stack[++top] = *begin;
                count++;
            }
            else {
                if (stack[top] == *begin) {
                    if (count != k - 1) {
                        count++;
                        stack[++top] = *begin;
                    }
                    else {
                        top -= k - 1;
                        count = (top == -1) ? 0 : 1;
                        kflag = true;
                    }
                }
                else {
                    stack[++top] = *begin;
                    count = 1;
                }
            }
            begin++;
        }
        stack[++top] = '\0';
        top = -1;
        begin = stack;
    }

    return stack;
}
