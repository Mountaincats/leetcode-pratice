/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* rotateRight(struct ListNode* head, int k) {
    if (head == NULL) return head;
    
    struct ListNode *tail = NULL, *curr = head;
    int num = 0;
    while (curr != NULL) {
        num++;
        tail = curr;
        curr = curr->next;
    }
    tail->next = head;

    num = num - k % num;
    while (num != 0) {
        tail = head;
        head = head->next;
        num--;
    }
    tail->next = NULL;
    return head;
}