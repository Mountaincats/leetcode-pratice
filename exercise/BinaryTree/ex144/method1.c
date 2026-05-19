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
int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }
    
    int* result = malloc(sizeof(int) * 100);
    int index = 0;
    *returnSize = 0;

    struct TreeNode** stack = malloc(sizeof(struct TreeNode*) * 100);
    int top = 0;
    stack[0] = root;

    while (top != -1) {
        struct TreeNode* cur = stack[top--];
        result[index++] = cur->val;
        (*returnSize)++;
        if (cur->right != NULL) stack[++top] = cur->right;
        if (cur->left != NULL) stack[++top] = cur->left;
    }

    return result;
}