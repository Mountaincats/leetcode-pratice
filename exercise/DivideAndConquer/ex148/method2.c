/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

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

struct ListNode* sortList(struct ListNode* head) {
    if (head == NULL) return head;

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
            struct ListNode* l1 = cur;
            for (int i = 1; i < sublength && cur->next != NULL; i++) {
                cur = cur->next;
            }

            struct ListNode* l2 = cur->next;
            cur->next = NULL;
            cur = l2;
            for (int i = 1; i < sublength && cur != NULL; i++) {
                cur = cur->next;
            }

            struct ListNode* next = NULL;
            if (cur != NULL) {
                next = cur->next;
                cur->next = NULL;
            }

            struct ListNode* merged = mergeList(l1, l2);
            pre->next = merged;
            while (pre->next != NULL) {
                pre = pre->next;
            }
            cur = next;
        }
    }

    tmp = dummy->next;
    free(dummy);
    return tmp;
}