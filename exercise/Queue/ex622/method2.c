typedef struct QNode{
    int value;
    struct QNode *next;
} QNode;

typedef struct {
    struct QNode *front;
    struct QNode *rear;
    int capacity;
    int size;
} MyCircularQueue;


MyCircularQueue* myCircularQueueCreate(int k) {
    MyCircularQueue *obj = malloc(sizeof(MyCircularQueue));
    obj->capacity = k;
    obj->size = 0;
    obj->front = obj->rear = NULL;

    return obj;
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
    if (obj->size == obj->capacity) return false;

    QNode *ins = malloc(sizeof(QNode));
    ins->next = NULL;
    ins->value = value;

    if (obj->size != 0) {
        obj->rear->next = ins;
        obj->rear = ins;
    }
    else {
        obj->rear = obj->front = ins;
    }

    obj->size++;

    return true;
}

bool myCircularQueueDeQueue(MyCircularQueue* obj) {
    if (obj->size == 0) return false;

    if (obj->size == 1) obj->rear = NULL;
    QNode *tmp = obj->front;
    obj->front = obj->front->next;
    free(tmp);

    obj->size--;

    return true;
}

int myCircularQueueFront(MyCircularQueue* obj) {
    if (obj->size == 0) return -1;
    return obj->front->value;
}

int myCircularQueueRear(MyCircularQueue* obj) {
    if (obj->size == 0) return -1;
    return obj->rear->value;
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
    if (obj->size == 0) return true;
    else return false;
}

bool myCircularQueueIsFull(MyCircularQueue* obj) {
    if (obj->size == obj->capacity) return true;
    else return false;
}

void myCircularQueueFree(MyCircularQueue* obj) {
    if (obj == NULL) return;
    QNode *index = obj->front;
    while (index != NULL) {
        QNode *tmp = index->next;
        free(index);
        index = tmp;
    }
    free(obj);
}

/**
 * Your MyCircularQueue struct will be instantiated and called as such:
 * MyCircularQueue* obj = myCircularQueueCreate(k);
 * bool param_1 = myCircularQueueEnQueue(obj, value);
 
 * bool param_2 = myCircularQueueDeQueue(obj);
 
 * int param_3 = myCircularQueueFront(obj);
 
 * int param_4 = myCircularQueueRear(obj);
 
 * bool param_5 = myCircularQueueIsEmpty(obj);
 
 * bool param_6 = myCircularQueueIsFull(obj);
 
 * myCircularQueueFree(obj);
*/