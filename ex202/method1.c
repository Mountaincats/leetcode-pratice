#include<stdbool.h>
#include<stddef.h>

struct hashTable {
    int key;
    int val;
    UT_hash_handle hh;
};

struct hashTable* hashtable;

struct hashTable* find(int ikey) {
    struct hashTable* tmp;
    HASH_FIND_INT(hashtable, &ikey, tmp);
    return tmp;
}

void insert(int ikey, int ival) {
    struct hashTable* it = find(ikey);
    if(it == NULL) {
        struct hashTable* tmp = malloc(sizeof(struct hashTable));
        tmp->key = ikey, tmp->val = ival;
        HASH_ADD_INT(hashtable, key, tmp);
    }
    else {
        it->val = ival;
    }
}

bool isHappy(int n) {
    hashtable = NULL;

    int temp = n;
    int key = n;
    while (true) {
        int val = 0;
        while (temp) {
            int num = temp % 10;
            val += num * num;
            temp /= 10;
        }

        if (val == 1) return true; 

        struct hashTable* it = find(val);
        if (it == NULL) {
            insert(key, val);
            key = temp = val;
        }
        else return false;
    }
}