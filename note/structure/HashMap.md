## 哈希表
[TOC]

### 一、uthash库
**1. 介绍**
- [仓库地址](https://github.com/troydhanson/uthash)
- [使用文档](https://troydhanson.github.io/uthash/)

**2. API**
```c
#include "uthash.h"
/* Convenience macros */
// 1. the structure’s UT_hash_handle field must be named hh
// 2. for add or find, the key field must be of type int or char[] or pointer

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