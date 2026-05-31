/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseBetween(struct ListNode* head, int left, int right) {
    struct ListNode dummyNode;
    dummyNode.next = head;

    struct ListNode* prev = &dummyNode;
    
    for (int i = 0; i < left - 1; i++) {
        prev = prev->next;
    }

    struct ListNode* curr = prev->next;
    struct ListNode* next;
    for (int i = 0; i < right - left; i++) {
        next = curr->next;
        curr->next = next->next;
        next->next = prev->next;
        prev->next = next;
    }
    return dummyNode.next;
}