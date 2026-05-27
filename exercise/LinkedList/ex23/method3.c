/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* mergeLists(struct ListNode* l1, struct ListNode* l2) {
    // if (!l1 || !l2) return l1 ? l1 : l2;

    struct ListNode head, *tail;
    head.next = NULL;
    tail = &head;

    while (l1 && l2) {
        if (l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
        }
        else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;

    return head.next;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0) return NULL;

    while (listsSize != 1) {
        int temp_listsSize = listsSize;
        listsSize = (listsSize + 1) >> 1;

        int store_index = 0, index = 0;
        for (; store_index < listsSize - 1; store_index++, index += 2) {
            lists[store_index] = mergeLists(lists[index], lists[index + 1]);
        }

        if (index + 2 > temp_listsSize) lists[store_index] = lists[index];
        else lists[store_index] = mergeLists(lists[index], lists[index + 1]);
    }

    return lists[0];
}