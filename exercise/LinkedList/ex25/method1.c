/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* reverse(struct ListNode* head) {
    struct ListNode *curr = head, *prev = NULL;
    while (curr != NULL) {
        struct ListNode* tmp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = tmp;
    }

    return prev;
}

struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    struct ListNode hair;
    hair.next = head;
    struct ListNode *tail = &hair;
    struct ListNode *prev = &hair, *next;
    while (true) {
        for (int i = 0; i < k; i++) {
            if (tail->next == NULL) return hair.next;
            tail = tail->next;
        }
        next = tail->next;
        tail->next = NULL;

        prev->next = reverse(head);
        head->next = next;

        prev = head;
        head = next;
        tail = prev;
    }
}