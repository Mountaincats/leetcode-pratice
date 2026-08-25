## 链表
[TOC]

---

### 一、理论

**1. 主要操作**
- 删除、查找、遍历
- 翻转单向链表
- 查找中间节点
- 单向链表判环、找入环节点
- 旋转链表
- 排序

**2. 设计技巧**
- 添加辅助头节点(hair)、head、tail、prev、next指针
  - 头节点可能发生变化时建议添加虚拟头节点dummyhead
- 快慢指针

---

### 二、排序链表

比较适合链表的排序算法是归并排序，其时间复杂度为 **$O(n \log n)$**，空间复杂度是 **$O(1)$**。实现代码如下：

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/* 合并两个有序链表 */
struct ListNode* mergeList(struct ListNode* l1, struct ListNode* l2) {
  struct ListNode *l1_cur = l1, *l2_cur = l2;
  struct ListNode dummy;
  struct ListNode* cur = &dummy;
  while (l1_cur != NULL && l2_cur != NULL) {
    if (l1_cur->val <= l2_cur->val) {
      cur->next = l1_cur;
      l1_cur = l1_cur->next;
    }
    else {
      cur->next = l2_cur;
      l2_cur = l2_cur->next;
    }
    cur = cur->next;
  }

  cur->next = NULL;
  if (l1_cur != NULL) cur->next = l1_cur;
  if (l2_cur != NULL) cur->next = l2_cur;

  return dummy.next;
}

/* 排序链表 */
struct ListNode* sortList(struct ListNode* head) {
  if (head == NULL) return head;

  // 得到链表长度
  int length = 0;
  struct ListNode* tmp = head;
  while (tmp != NULL) {
    length++;
    tmp = tmp->next;
  }

  struct ListNode* dummy = malloc(sizeof(struct ListNode));
  dummy->next = head;

  for (int sublength = 1; sublength < length; sublength <<= 1) {
    struct ListNode *pre = dummy, *cur = dummy->next;
    while (cur != NULL) {
      // l1 指向第一个未合并的长为 sublength 的子链表
      // 若 l1 长度不足 sublength，则中止，后续 l2, next 为 NULL
      // 循环结束后 cur 指向 l1 尾结点
      struct ListNode* l1 = cur;
      for (int i = 1; i < sublength && cur->next != NULL; i++) {
        cur = cur->next;
      }

      // l2 指向第二个未合并的长为 sublength 的子链表
      // 若 l2 长度不足 sublength，则中止，后续 next 为 NULL
      // 循环结束后 cur 指向 l2 尾结点
      struct ListNode* l2 = cur->next;
      cur->next = NULL;
      cur = l2;
      for (int i = 1; i < sublength && cur != NULL; i++) {
        cur = cur->next;
      }

      // 若 l2 长度为 sublength，说明可能仍有下一个节点，此时 cur != NULL
      // 最后 next 等于 NULL，或指向下一个待合并子链表
      struct ListNode* next = NULL;
      if (cur != NULL) {
        next = cur->next;
        cur->next = NULL;
      }

      // 合并两个子链表
      struct ListNode* merged = mergeList(l1, l2);

      // pre 是 dummy 或上一个合并的子链表的尾节点，将其指向新合并的子链表
      pre->next = merged;
      // 之后让 pre 指向新合并的子链表的尾节点
      while (pre->next != NULL) {
        pre = pre->next;
      }
      // 将 cur 指向新合并子链表的下一个节点
      cur = next;
    }
  }

  tmp = dummy->next;
  free(dummy);
  return tmp;
}
```