/**
 * Your AllOne struct will be instantiated and called as such:
 * AllOne* obj = allOneCreate();
 * allOneInc(obj, key);
 
 * allOneDec(obj, key);
 
 * char* param_3 = allOneGetMaxKey(obj);
 
 * char* param_4 = allOneGetMinKey(obj);
 
 * allOneFree(obj);
*/

// 无法同时存在多个独立的 AllOne 实例
// 多线程 / 多次 allOneCreate()会互相污染

typedef struct AllOne {
    int count;
    struct AllOne* prev;
    struct AllOne* next;

    struct KeyNode {
        char* key;
        UT_hash_handle hh;
    }* keys;
} AllOne;

typedef struct {
    char* key;
    AllOne* node;
    UT_hash_handle hh;
} KeyMap;

static KeyMap* nodes = NULL;

/* ---------- helpers ---------- */

static AllOne* new_node(int count) {
    AllOne* node = (AllOne*)calloc(1, sizeof(AllOne));
    node->count = count;
    return node;
}

/* 在 prev 和 next 之间插入 node */
static void insert_between(AllOne* node, AllOne* prev, AllOne* next) {
    node->prev = prev;
    node->next = next;
    if (prev) prev->next = node;
    if (next) next->prev = node;
}

/* 从链表中删除 node */
static void remove_node(AllOne* node) {
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;
    free(node);
}

/* ---------- API ---------- */

AllOne* allOneCreate() {
    nodes = NULL;
    return new_node(0); // dummy head
}

void allOneInc(AllOne* head, char* key) {
    KeyMap* km;
    HASH_FIND_STR(nodes, key, km);

    AllOne* cur = km ? km->node : NULL;
    AllOne* target = NULL;

    if (!cur) {
        target = head->next;
        if (!target || target->count > 1) {
            target = new_node(1);
            insert_between(target, head, head->next);
        }
    } else {
        int nextCount = cur->count + 1;
        if (!cur->next || cur->next->count > nextCount) {
            target = new_node(nextCount);
            insert_between(target, cur, cur->next);
        } else {
            target = cur->next;
        }

        /* 从 cur 中移除 key */
        struct KeyNode* kn;
        HASH_FIND_STR(cur->keys, key, kn);
        HASH_DEL(cur->keys, kn);
        free(kn);

        if (!cur->keys) remove_node(cur);
    }

    /* 加入 target */
    struct KeyNode* kn = (struct KeyNode*)malloc(sizeof(*kn));
    kn->key = key;
    HASH_ADD_KEYPTR(hh, target->keys, key, strlen(key), kn);

    /* 更新 map */
    if (km) km->node = target;
    else {
        km = (KeyMap*)malloc(sizeof(*km));
        km->key = key;
        km->node = target;
        HASH_ADD_KEYPTR(hh, nodes, key, strlen(key), km);
    }
}

/* dec */
void allOneDec(AllOne* head, char* key) {
    KeyMap* km;
    HASH_FIND_STR(nodes, key, km);
    AllOne* cur = km->node;

    if (cur->count == 1) {
        /* 删除 key */
        struct KeyNode* kn;
        HASH_FIND_STR(cur->keys, key, kn);
        HASH_DEL(cur->keys, kn);
        free(kn);

        HASH_DEL(nodes, km);
        free(km);

        if (!cur->keys) remove_node(cur);
        return;
    }

    int prevCount = cur->count - 1;
    AllOne* target = NULL;

    if (!cur->prev || cur->prev->count < prevCount) {
        target = new_node(prevCount);
        insert_between(target, cur->prev, cur);
    } else {
        target = cur->prev;
    }

    /* 从 cur 移走 */
    struct KeyNode* kn;
    HASH_FIND_STR(cur->keys, key, kn);
    HASH_DEL(cur->keys, kn);
    free(kn);

    /* 加入 target */
    kn = (struct KeyNode*)malloc(sizeof(*kn));
    kn->key = key;
    HASH_ADD_KEYPTR(hh, target->keys, key, strlen(key), kn);

    km->node = target;

    if (!cur->keys) remove_node(cur);
}

char* allOneGetMaxKey(AllOne* head) {
    AllOne* tail = head;
    while (tail->next) tail = tail->next;
    if (!tail || !tail->keys) return "";
    return tail->keys->key;
}

char* allOneGetMinKey(AllOne* head) {
    if (!head->next || !head->next->keys) return "";
    return head->next->keys->key;
}

void allOneFree(AllOne* head) {
    AllOne* cur = head;
    while (cur) {
        AllOne* nxt = cur->next;

        struct KeyNode *k, *tmp;
        HASH_ITER(hh, cur->keys, k, tmp) {
            HASH_DEL(cur->keys, k);
            free(k);
        }
        free(cur);
        cur = nxt;
    }

    KeyMap *m, *mtmp;
    HASH_ITER(hh, nodes, m, mtmp) {
        HASH_DEL(nodes, m);
        free(m);
    }
}
