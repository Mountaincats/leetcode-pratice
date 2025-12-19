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

// next() 是纯函数，更容易被内联和优化
int next(int n) {
    int val = 0;
    while (n) {
        int num = n % 10;
        val += num * num;
        n /= 10;
    }

    return val;
}

bool isHappy(int n) {
    hashtable = NULL;

    int key = n;
    while (true) {
        int val = next(key);

        if (val == 1) return true; 

        struct hashTable* it = find(val);
        if (it == NULL) {
            insert(key, val);
            key = val;
        }
        else return false;
    }
}

// bool isHappy(int n) {
//     hashtable = NULL;

//     int temp = n;
//     // 跨循环状态变量 temp，优化空间更小
//     int key = n;
//     while (true) {
//         int val = 0;
//         while (temp) {
//             int num = temp % 10;
//             val += num * num;
//             temp /= 10;
//         }

//         if (val == 1) return true; 

//         struct hashTable* it = find(val);
//         if (it == NULL) {
//             insert(key, val);
//             key = temp = val;
//         }
//         else return false;
//     }
// }