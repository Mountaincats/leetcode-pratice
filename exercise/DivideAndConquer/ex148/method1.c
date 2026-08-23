/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* middleNode(struct ListNode* head) {
    struct ListNode *slow = head, *fast = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

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
    if (head == NULL || head->next == NULL) return head;

    struct ListNode* mid = middleNode(head);

    struct ListNode* r_interval = sortList(mid->next);
    mid->next = NULL;
    struct ListNode* l_interval = sortList(head);

    return mergeList(l_interval, r_interval);
}