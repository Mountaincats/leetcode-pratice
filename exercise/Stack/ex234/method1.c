/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
bool isPalindrome(struct ListNode* head) {
    int num[100000];
    int i = 0, j = 0, count = 0;
    while (head != NULL) {
        num[count++] = head->val;
        head = head->next;
    }
    j = count - 1;
    count /= 2;
    while (count-- != 0) {
        if (num[i++] != num[j--]) return false;
    }
    return true;
}