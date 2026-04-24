/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int height(struct TreeNode* root) {
    if (root == NULL) return 0;

    int left = height(root->left);
    if (left < 0) return -1;
    int right = height(root->right);
    if (right < 0 || fabs(left - right) > 1) return -1;
    else return fmax(left, right) + 1;
}

bool isBalanced(struct TreeNode* root) {
    return height(root) >= 0;
}