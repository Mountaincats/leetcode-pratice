/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* reverse(struct ListNode* head) {
    struct ListNode *prev = NULL;
    while (head != NULL) {
        struct ListNode* next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

struct ListNode* findmid(struct ListNode* head) {
    struct ListNode *slow = head, *fast = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

bool isPalindrome(struct ListNode* head) {
    struct ListNode* halflist = findmid(head);
    struct ListNode* last = reverse(halflist->next);
    halflist = last;

    while (halflist != NULL) {
        if (halflist->val != head->val) return false;
        halflist = halflist->next;
        head = head->next;
    }

    reverse(last);
    return true;
}