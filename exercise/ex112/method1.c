/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool backtrack(struct TreeNode* root, int targetSum, int sum) {
    if (root->left == NULL && root->right == NULL && sum + root->val == targetSum) return true;
    if (root->left != NULL && backtrack(root->left, targetSum, sum + root->val)) return true;
    if (root->right != NULL && backtrack(root->right, targetSum, sum + root->val)) return true;

    return false;
}

bool hasPathSum(struct TreeNode* root, int targetSum) {
    if (root == NULL) return false;
    return backtrack(root, targetSum, 0);
}