/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

// 创建新链表
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode head;
    head.next = NULL;
    struct ListNode* curr = &head;

    int c = 0;
    while (l1 != NULL && l2 != NULL) {
        curr->next = malloc(sizeof(struct ListNode));
        curr = curr->next;
        curr->next = NULL;

        int val = l1->val + l2->val + c;
        c = val / 10;
        curr->val = val - 10 * c;

        l1 = l1->next;
        l2 = l2->next;
    }

    struct ListNode* l = l1 ? l1 : l2;
    while (l != NULL) {
        curr->next = malloc(sizeof(struct ListNode));
        curr = curr->next;
        curr->next = NULL;

        int val = c + l->val;
        c = val / 10;
        curr->val = val - 10 * c;
        
        l = l->next;
    }
    if (c != 0) {
        curr->next = malloc(sizeof(struct ListNode));
        curr = curr->next;
        curr->next = NULL;
        curr->val = c;
    }

    return head.next;
}

// 不创建新链表
// struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
//     if (l1 == NULL || l2 == NULL) return l1 ? l1 : l2;

//     struct ListNode* head = l1;
//     struct ListNode* prev = NULL;

//     int c = 0;
//     while (l1 != NULL && l2 != NULL) {
//         int val = l1->val + l2->val + c;
//         c = val / 10;
//         l1->val = val - 10 * c;

//         prev = l1;
//         l1 = l1->next;
//         l2 = l2->next;
//     }

//     struct ListNode* curr = l1 ? l1 : l2;
//     prev->next = curr;

//     while (c != 0 && curr != NULL) {
//         int val = curr->val + c;
//         c = val / 10;
//         curr->val = val - 10 * c;
        
//         curr = curr->next;
//         prev = prev->next;
//     }

//     if (c != 0) {
//         prev->next = malloc(sizeof(struct ListNode));
//         prev->next->val = 1;
//         prev->next->next = NULL;
//     }

//     return head;
// }