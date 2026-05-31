/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* swapPairs(struct ListNode* head) {
    struct ListNode hair;
    hair.next = head;

    struct ListNode* prev = &hair;
    while (head != NULL && head->next != NULL) {
        struct ListNode* next = head->next->next;
        prev->next = head->next;
        prev = head;

        head->next->next = head;
        head->next = next;
        head = next;
    }

    return hair.next;
}