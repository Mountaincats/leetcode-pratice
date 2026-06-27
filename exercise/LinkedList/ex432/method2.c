typedef struct KeyNode {
    char* key;
    UT_hash_handle hh;
} KeyNode;

typedef struct Bucket {
    int count;
    KeyNode* keys;
    struct Bucket* prev;
    struct Bucket* next;
} Bucket;

typedef struct {
    char* key;
    Bucket* bucket;
    UT_hash_handle hh;
} KeyMap;

typedef struct {
    Bucket* head;
    KeyMap* map;
} AllOne;

/* ---------- helpers ---------- */

static Bucket* new_bucket(int count) {
    Bucket* b = calloc(1, sizeof(Bucket));
    b->count = count;
    return b;
}

static void insert_after(Bucket* pos, Bucket* node) {
    node->prev = pos;
    node->next = pos->next;
    if (pos->next) pos->next->prev = node;
    pos->next = node;
}

static void remove_bucket(Bucket* b) {
    if (b->prev) b->prev->next = b->next;
    if (b->next) b->next->prev = b->prev;
    free(b);
}

/* ---------- API ---------- */

AllOne* allOneCreate() {
    AllOne* obj = calloc(1, sizeof(AllOne));
    obj->head = new_bucket(0); // dummy head
    return obj;
}

void allOneInc(AllOne* obj, char* key) {
    KeyMap* km;
    HASH_FIND_STR(obj->map, key, km);

    Bucket* cur = km ? km->bucket : NULL;
    Bucket* target = NULL;

    if (!cur) {
        target = obj->head->next;
        if (!target || target->count > 1) {
            target = new_bucket(1);
            insert_after(obj->head, target);
        }
    } else {
        int nc = cur->count + 1;
        if (!cur->next || cur->next->count > nc) {
            target = new_bucket(nc);
            insert_after(cur, target);
        } else {
            target = cur->next;
        }

        KeyNode* kn;
        HASH_FIND_STR(cur->keys, key, kn);
        HASH_DEL(cur->keys, kn);
        free(kn);

        if (!cur->keys) remove_bucket(cur);
    }

    KeyNode* kn = malloc(sizeof(KeyNode));
    kn->key = key;
    HASH_ADD_KEYPTR(hh, target->keys, key, strlen(key), kn);

    if (km) {
        km->bucket = target;
    } else {
        km = malloc(sizeof(KeyMap));
        km->key = key;
        km->bucket = target;
        HASH_ADD_KEYPTR(hh, obj->map, key, strlen(key), km);
    }
}

void allOneDec(AllOne* obj, char* key) {
    KeyMap* km;
    HASH_FIND_STR(obj->map, key, km);
    if (!km) return;

    Bucket* cur = km->bucket;

    if (cur->count == 1) {
        KeyNode* kn;
        HASH_FIND_STR(cur->keys, key, kn);
        HASH_DEL(cur->keys, kn);
        free(kn);

        HASH_DEL(obj->map, km);
        free(km);

        if (!cur->keys) remove_bucket(cur);
        return;
    }

    int pc = cur->count - 1;
    Bucket* target = NULL;

    if (!cur->prev || cur->prev->count < pc) {
        target = new_bucket(pc);
        insert_after(cur->prev, target);
    } else {
        target = cur->prev;
    }

    KeyNode* kn;
    HASH_FIND_STR(cur->keys, key, kn);
    HASH_DEL(cur->keys, kn);
    free(kn);

    kn = malloc(sizeof(KeyNode));
    kn->key = key;
    HASH_ADD_KEYPTR(hh, target->keys, key, strlen(key), kn);

    km->bucket = target;

    if (!cur->keys) remove_bucket(cur);
}

char* allOneGetMaxKey(AllOne* obj) {
    Bucket* cur = obj->head;
    while (cur->next) cur = cur->next;
    return cur->keys ? cur->keys->key : "";
}

char* allOneGetMinKey(AllOne* obj) {
    return (obj->head->next && obj->head->next->keys)
           ? obj->head->next->keys->key : "";
}

void allOneFree(AllOne* obj) {
    Bucket* cur = obj->head;
    while (cur) {
        Bucket* nxt = cur->next;
        KeyNode *k, *tmp;
        HASH_ITER(hh, cur->keys, k, tmp) {
            HASH_DEL(cur->keys, k);
            free(k);
        }
        free(cur);
        cur = nxt;
    }

    KeyMap *m, *tmp;
    HASH_ITER(hh, obj->map, m, tmp) {
        HASH_DEL(obj->map, m);
        free(m);
    }

    free(obj);
}