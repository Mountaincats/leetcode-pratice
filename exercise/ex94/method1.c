/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    *returnSize = 0;
    int* res = malloc(sizeof(int) * 501);
    
    struct TreeNode** stack = malloc(sizeof(struct TreeNode*) * 501);
    int top = 0;

    while (root != NULL || top > 0) {
        while (root != NULL) {
            stack[top++] = root;
            root = root->left;
        }
        root = stack[--top];
        res[(*returnSize)++] = root->val;
        root = root->right;
    }

    return res;
}