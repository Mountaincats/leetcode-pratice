bool isValid(char* s) {
    char pair[256] = {0};
    pair[')'] = '(';
    pair[']'] = '[';
    pair['}'] = '{';
    char* stack = malloc(sizeof(char) * strlen(s));
    int top = -1;
    while (*s != '\0') {
        if (top != -1 && pair[*s] == stack[top]) top--;
        else stack[++top] = *s;
        s++;
    }

		free(stack);

		return top == -1
}