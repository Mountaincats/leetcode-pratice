typedef struct {
    int front;
    int rear;
    int capacity;
    int *elements;
} MyCircularDeque;


MyCircularDeque* myCircularDequeCreate(int k) {
    MyCircularDeque *obj = malloc(sizeof(MyCircularDeque));
    obj->capacity = k + 1;
    obj->elements = malloc(sizeof(int) * obj->capacity);
    obj->front = 0;
    obj->rear = 0;

    return obj;
}

bool myCircularDequeInsertFront(MyCircularDeque* obj, int value) {
    if ((obj->rear + 1) % obj->capacity == obj->front) return false;
    obj->front = (obj->front + obj->capacity - 1) % obj->capacity;
    obj->elements[obj->front] = value;
    return true;
}

bool myCircularDequeInsertLast(MyCircularDeque* obj, int value) {
    if ((obj->rear + 1) % obj->capacity == obj->front) return false;
    obj->elements[obj->rear] = value;
    obj->rear = (obj->rear + 1) % obj->capacity;
    return true;
}

bool myCircularDequeDeleteFront(MyCircularDeque* obj) {
    if (obj->front == obj->rear) return false;
    obj->front = (obj->front + 1) % obj->capacity;
    return true;
}

bool myCircularDequeDeleteLast(MyCircularDeque* obj) {
    if (obj->front == obj->rear) return false;
    obj->rear = (obj->rear + obj->capacity - 1) % obj->capacity;
    return true;
}

int myCircularDequeGetFront(MyCircularDeque* obj) {
    if (obj->front == obj->rear) return -1;
    return obj->elements[obj->front];
}

int myCircularDequeGetRear(MyCircularDeque* obj) {
    if (obj->front == obj->rear) return -1;
    return obj->elements[(obj->rear + obj->capacity - 1) % obj->capacity];
}

bool myCircularDequeIsEmpty(MyCircularDeque* obj) {
    return obj->front == obj->rear;
}

bool myCircularDequeIsFull(MyCircularDeque* obj) {
    return (obj->rear + 1) % obj->capacity == obj->front;
}

void myCircularDequeFree(MyCircularDeque* obj) {
    if (obj == NULL) return;
    free(obj->elements);
    free(obj);
}

/**
 * Your MyCircularDeque struct will be instantiated and called as such:
 * MyCircularDeque* obj = myCircularDequeCreate(k);
 * bool param_1 = myCircularDequeInsertFront(obj, value);
 
 * bool param_2 = myCircularDequeInsertLast(obj, value);
 
 * bool param_3 = myCircularDequeDeleteFront(obj);
 
 * bool param_4 = myCircularDequeDeleteLast(obj);
 
 * int param_5 = myCircularDequeGetFront(obj);
 
 * int param_6 = myCircularDequeGetRear(obj);
 
 * bool param_7 = myCircularDequeIsEmpty(obj);
 
 * bool param_8 = myCircularDequeIsFull(obj);
 
 * myCircularDequeFree(obj);
*/