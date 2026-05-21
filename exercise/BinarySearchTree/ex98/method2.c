/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isValidBST(struct TreeNode* root) {
    struct TreeNode** stack = malloc(sizeof(struct TreeNode*) * 10000);
    int top = 0;
    long long inorder = (long long)INT_MIN - 1;

    while (top != 0 || root != NULL) {
        while (root != NULL) {
            stack[top++] = root;
            root = root->left;
        }
        root = stack[--top];
        if (root->val > inorder) inorder = root->val;
        else return false;
        root = root->right;
    }

    return true;
}