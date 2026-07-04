/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode *slow = &dummy, *fast = &dummy;
    while (n-- != 0) {
        fast = fast->next;
    }

    while (fast->next != NULL) {
        fast = fast->next;
        slow = slow->next;
    }
    
    struct ListNode* tmp = slow->next;
    slow->next = tmp->next;
    free(tmp);

    return dummy.next;
}