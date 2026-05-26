/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* mergeLists(struct ListNode* l1, struct ListNode* l2) {
    if (!l1 || !l2) return l1 ? l1 : l2;

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
    struct ListNode* head = NULL;

    for (int i = 0; i < listsSize; i++) {
        head = mergeLists(head, lists[i]);
    }

    return head;
}