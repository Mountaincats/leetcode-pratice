/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* insertionSortList(struct ListNode* head) {
    if (head == NULL) {
        return head;
    }

    struct ListNode* dummy = malloc(sizeof(struct ListNode));
    dummy->next = head;

    struct ListNode *last = head, *cur = head->next;
    while (cur != NULL) {
        if (cur->val >= last->val) {
            last = cur;
        }
        else {
            struct ListNode* pre = dummy;
            while (pre->next->val <= cur->val) pre = pre->next;
            last->next = cur->next;
            cur->next = pre->next;
            pre->next = cur;
        }
        cur = last->next;
    }

    return dummy->next;
}/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* insertionSortList(struct ListNode* head) {
    if (head == NULL) {
        return head;
    }

    struct ListNode* dummy = malloc(sizeof(struct ListNode));
    dummy->next = head;

    struct ListNode *last = head, *cur = head->next;
    while (cur != NULL) {
        if (cur->val >= last->val) {
            last = cur;
        }
        else {
            struct ListNode* pre = dummy;
            while (pre->next->val <= cur->val) pre = pre->next;
            last->next = cur->next;
            cur->next = pre->next;
            pre->next = cur;
        }
        cur = last->next;
    }

    return dummy->next;
}