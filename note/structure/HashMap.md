## 哈希表
[TOC]

### 一、uthash库
**1. 介绍**
- [仓库地址](https://github.com/troydhanson/uthash)
- [使用文档](https://troydhanson.github.io/uthash/)

**2. API**
```c
/* Convenience macros */
// 1. the structure’s UT_hash_handle field must be named hh
// 2. for add or find, the key field must be of type int or char[] or pointer

#include "uthash.h"

// UT_hash_handle
typedef struct UT_hash_handle {
   struct UT_hash_table *tbl;
   void *prev;                       /* prev element in app order      */
   void *next;                       /* next element in app order      */
   struct UT_hash_handle *hh_prev;   /* previous hh in bucket order    */
   struct UT_hash_handle *hh_next;   /* next hh in bucket order        */
   const void *key;                  /* ptr to enclosing struct's key  */
   unsigned keylen;                  /* enclosing struct's key len     */
   unsigned hashv;                   /* result of hash-fcn(key)        */
} UT_hash_handle;

// int
HASH_ADD_INT(head, keyfield_name, item_ptr)
HASH_REPLACE_INT(head, keyfield_name, item_ptr, replaced_item_ptr)
HASH_FIND_INT(head, key_ptr, item_ptr)

// str
HASH_ADD_STR(head, keyfield_name, item_ptr)
HASH_REPLACE_STR(head, keyfield_name, item_ptr, replaced_item_ptr)
HASH_FIND_STR(head, key_ptr, item_ptr)

// ptr
HASH_ADD_PTR(head, keyfield_name, item_ptr)
HASH_REPLACE_PTR(head, keyfield_name, item_ptr, replaced_item_ptr)
HASH_FIND_PTR(head, key_ptr, item_ptr)

// other operations
HASH_DEL(head, item_ptr)
HASH_SORT(head, cmp)
HASH_COUNT(head)
```

```c
/* General macros */

// Iterating
HASH_ITER(hh, head, current, tmp)
```

**3. 完整示例**
```c
#include <stdio.h>   /* printf */
#include <stdlib.h>  /* atoi, malloc */
#include <string.h>  /* strcpy */
#include "uthash.h"

struct my_struct {
    int id;                    /* key */
    char name[21];
    UT_hash_handle hh;         /* makes this structure hashable */
};

struct my_struct *users = NULL;

void add_user(int user_id, const char *name)
{
    struct my_struct *s;

    HASH_FIND_INT(users, &user_id, s);  /* id already in the hash? */
    if (s == NULL) {
        s = (struct my_struct*)malloc(sizeof *s);
        s->id = user_id;
        HASH_ADD_INT(users, id, s);  /* id is the key field */
    }
    strcpy(s->name, name);
}

struct my_struct *find_user(int user_id)
{
    struct my_struct *s;

    HASH_FIND_INT(users, &user_id, s);  /* s: output pointer */
    return s;
}

void delete_user(struct my_struct *user)
{
    HASH_DEL(users, user);  /* user: pointer to deletee */
    free(user);
}

void delete_all()
{
    struct my_struct *current_user;
    struct my_struct *tmp;

    HASH_ITER(hh, users, current_user, tmp) {
        HASH_DEL(users, current_user);  /* delete it (users advances to next) */
        free(current_user);             /* free it */
    }
}

void print_users()
{
    struct my_struct *s;

    for (s = users; s != NULL; s = (struct my_struct*)(s->hh.next)) {
        printf("user id %d: name %s\n", s->id, s->name);
    }
}

int by_name(const struct my_struct *a, const struct my_struct *b)
{
    return strcmp(a->name, b->name);
}

int by_id(const struct my_struct *a, const struct my_struct *b)
{
    return (a->id - b->id);
}

const char *getl(const char *prompt)
{
    static char buf[21];
    char *p;
    printf("%s? ", prompt); fflush(stdout);
    p = fgets(buf, sizeof(buf), stdin);
    if (p == NULL || (p = strchr(buf, '\n')) == NULL) {
        puts("Invalid input!");
        exit(EXIT_FAILURE);
    }
    *p = '\0';
    return buf;
}

int main()
{
    int id = 1;
    int running = 1;
    struct my_struct *s;
    int temp;

    while (running) {
        printf(" 1. add user\n");
        printf(" 2. add or rename user by id\n");
        printf(" 3. find user\n");
        printf(" 4. delete user\n");
        printf(" 5. delete all users\n");
        printf(" 6. sort items by name\n");
        printf(" 7. sort items by id\n");
        printf(" 8. print users\n");
        printf(" 9. count users\n");
        printf("10. quit\n");
        switch (atoi(getl("Command"))) {
            case 1:
                add_user(id++, getl("Name (20 char max)"));
                break;
            case 2:
                temp = atoi(getl("ID"));
                add_user(temp, getl("Name (20 char max)"));
                break;
            case 3:
                s = find_user(atoi(getl("ID to find")));
                printf("user: %s\n", s ? s->name : "unknown");
                break;
            case 4:
                s = find_user(atoi(getl("ID to delete")));
                if (s) {
                    delete_user(s);
                } else {
                    printf("id unknown\n");
                }
                break;
            case 5:
                delete_all();
                break;
            case 6:
                HASH_SORT(users, by_name);
                break;
            case 7:
                HASH_SORT(users, by_id);
                break;
            case 8:
                print_users();
                break;
            case 9:
                temp = HASH_COUNT(users);
                printf("there are %d users\n", temp);
                break;
            case 10:
                running = 0;
                break;
        }
    }

    delete_all();  /* free any structures */
    return 0;
}
```

### 二、理论
**1. 哈希冲突处理**
- 开放地址法：当哈希表未满时，处理冲突需要的“下一个”地址在该哈希表中寻找。会产生**聚集**现象，即哈希地址不同的元素争夺同一个后继哈希地址
  - 线性探测
  - 二次探测
- 链地址法：将所有哈希地址相同的记录链接成一个线性链表，不会产生元素**聚集**现象。uthash 采用此法解决冲突

**2. 哈希函数设计**
- 分布性：哈希函数需将键均匀分布在桶数组中，以减少冲突，保证 O(1) 的平均查找效率

**3. 数据结构设计**
- 全局(双向)链表(prev / next)：uthash 采用此法，用于方便遍历存在的节点，顺序由插入顺序决定，可被如 `HASH_SORT` 的操作重排
- 哈希桶链表(hh_prev / hh_next)：处理哈希冲突
- 动态扩容：当元素数量与桶数量的比值(**负载因子**)超过阈值时，哈希表会自动扩容并重新散列(Rehash)