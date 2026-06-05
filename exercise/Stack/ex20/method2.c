bool isValid(char* s) {
    int top = -1;
    for (int i = 0; s[i]; i++) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            s[++top] = s[i];
        } 
				else {
            if (top < 0) return false;
            if ((s[i] == ')' && s[top] != '(') ||
                (s[i] == ']' && s[top] != '[') ||
                (s[i] == '}' && s[top] != '{')) {
                return false;
            }
            top--;
        }
    }
    return top == -1;
}