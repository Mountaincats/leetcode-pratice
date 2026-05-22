/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* insertIntoBST(struct TreeNode* root, int val) {
    struct TreeNode* insert = malloc(sizeof(struct TreeNode));
    insert->val = val;
    insert->left = NULL;
    insert->right = NULL;

    if (root == NULL) return insert;

    struct TreeNode* pos = root;

    while (pos != NULL) {
        if (pos->val > val) {
            if (pos->left == NULL) {
                pos->left = insert;
                break;
            }
            else pos = pos->left;
        }
        else {
            if (pos->right == NULL) {
                pos->right = insert;
                break;
            }
            else pos = pos->right;
        }
    }

    return root;
}