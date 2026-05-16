/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* searchBST(struct TreeNode* root, int val) {
    while (root != NULL) {
        if (val == root->val) return root;
        root = (val > root->val) ? root->right : root->left;
    }
    return NULL;
}