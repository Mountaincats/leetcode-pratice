char* removeDuplicates(char* s) {
    char* stack = malloc(sizeof(char) * (strlen(s) + 1));
    int top = -1;
    while (*s != '\0') {
        if (top == -1) stack[++top] = *s;
        else {
            if (stack[top] == *s) top--;
            else stack[++top] = *s;
        }
        s++;
    }
    stack[++top] = '\0';

    return stack;
}