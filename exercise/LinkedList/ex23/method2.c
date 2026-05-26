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

struct ListNode* merge(struct ListNode** lists, int l, int r) {
    if (l == r) return lists[l];
    if (l > r) return NULL;
    int mid = (l + r) >> 1;
    return mergeLists(merge(lists, l, mid), merge(lists, mid + 1, r));
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    return merge(lists, 0, listsSize - 1);
}