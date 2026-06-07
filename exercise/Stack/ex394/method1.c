char* decodeString(char* s) {
    char* result = malloc(sizeof(char) * 100000);
    int* num = malloc(sizeof(int) * 30);
    int ctop = 0;
    int ntop = 0;
    
    while (*s != '\0') {
        if (isdigit(*s)) {
            int k = 0;
            do {
                k = 10 * k + (*(s++) - '0');
            } while (*s != '[');
            num[ntop++] = k;
        }
        else if (*s == '[' || isalpha(*s)) result[ctop++] = *(s++);
        else if (*(s++) == ']') {
            char tmp[100000];
            int count = 0;
            while (result[--ctop] != '[') {
                tmp[count++] = result[ctop];
            }

            int loop = num[--ntop];

            while (loop-- != 0) {
                for (int i = count - 1; i >= 0; i--) {
                    result[ctop++] = tmp[i];
                }
            }
        }
    }

    result[ctop] = '\0';

    free(num);
    return result;
}