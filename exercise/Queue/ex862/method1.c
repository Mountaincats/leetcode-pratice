typedef struct {
    int *buf;
    int head, tail;
    int cap;
} Deque;

Deque* dqCreate(int k) {
    Deque *d = malloc(sizeof(Deque));
    d->cap = k + 1;
    d->head = d->tail = 0;
    d->buf = malloc(sizeof(int) * d->cap);
    return d;
}

bool dqPushFront(Deque* d, int v) {
    if ((d->tail + 1) % d->cap == d->head) return false;
    d->head = (d->head - 1 + d->cap) % d->cap;
    d->buf[d->head] = v;
    return true;
}

bool dqPushBack(Deque* d, int v) {
    if ((d->tail + 1) % d->cap == d->head) return false;
    d->buf[d->tail] = v;
    d->tail = (d->tail + 1) % d->cap;
    return true;
}

bool dqPopFront(Deque* d) {
    if (d->tail == d->head) return false;
    d->head = (d->head + 1) % d->cap;
    return true;
}

bool dqPopBack(Deque* d) {
    if (d->tail == d->head) return false;
    d->tail = (d->tail - 1 + d->cap) % d->cap;
    return true;
}

int dqFront(Deque* d) {
    return d->tail == d->head ? -1 : d->buf[d->head];
}

int dqBack(Deque* d) {
    return d->tail == d->head ? -1 : d->buf[(d->tail - 1 + d->cap) % d->cap];
}

bool dqEmpty(Deque* d) {
    return d->tail == d->head;
}

bool dqFull(Deque* d) {
    return (d->tail + 1) % d->cap == d->head;
}

void dqFree(Deque* d) {
    free(d->buf);
    free(d);
}

int shortestSubarray(int* a, int n, int k) {
    long pre[n + 1];
    pre[0] = 0;
    for (int i = 0; i < n; i++)
        pre[i + 1] = pre[i] + a[i];

    int ans = n + 1;
    Deque *dq = dqCreate(n + 1);

    for (int i = 0; i <= n; i++) {
        while (!dqEmpty(dq) && pre[i] - pre[dqFront(dq)] >= k) {
            ans = (ans < i - dqFront(dq)) ? ans : i - dqFront(dq);
            dqPopFront(dq);
        }
        while (!dqEmpty(dq) && pre[dqBack(dq)] >= pre[i])
            dqPopBack(dq);
        dqPushBack(dq, i);
    }

    dqFree(dq);
    return ans <= n ? ans : -1;
}