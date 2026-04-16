/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct QueNode {
    struct TreeNode* p;
    struct QueNode* next;
}

void init(struct QueNode** p, struct TreeNode* t) {
    (*p) = (struct QueNode*)malloc(sizeof(struct QueNode));
    (*p)->p = t;
    (*p)->next = NULL;
}

int maxDepth(struct TreeNode* root) {
    if(root == NULL) return 0;
    struct QueNode *left, *right;
    init(&left, root);
    right = left;

    
}