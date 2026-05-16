/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void backtrack(struct TreeNode* root, int* left_node_sum, bool is_left) {
    if (root->left == NULL && root->right == NULL && is_left) *left_node_sum += root->val;
    else if (root->left == NULL && root->right == NULL && !is_left) return;
    else {
        if (root->left != NULL) backtrack(root->left, left_node_sum, true);
        if (root->right != NULL) backtrack(root->right, left_node_sum, false);
    }
}

int sumOfLeftLeaves(struct TreeNode* root) {
    int sum = 0;
    backtrack(root, &sum, false);

    return sum;
}