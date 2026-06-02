char* simplifyPath(char* path) {
    char* curr = path;
    char* head = path;
    while (*curr != '\0') {
        switch (*curr) {
            case '/': {
                if (head - 1 != path) {
                    *head = '/';
                    head++;
                }
                do {
                    curr++;
                } while (*curr == '/');
                if (*curr == '\0') {
                    if (head - 1 != path) head--;
                }
                break;
            }
            case '.': {
                if (curr[1] == '/' || curr[1] == '\0') {
                    if (head - 1 != path) head--;
                    curr++;
                    break;
                }
                else if (curr[1] == '.') {
                    if (curr[2] == '/' || curr[2] == '\0') {
                        if (head - 1 == path) {
                            curr += 2;
                            break;
                        }
                        head--;
                        while (*(--head) != '/');
                        if (head == path) head++;
                        curr += 2;
                        break;
                    }
                }
                // go through
            }
            default: {
                do {
                    *head = *curr;
                    head++;
                    curr++;
                } while (*curr != '/' && *curr != '\0');
                break;
            }
        }
    }
    *head = '\0';

    return path;
}