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

    struct TreeNode** pos = &root;

    while (true) {
        if (*pos == NULL) {
            *pos = insert;
            break;
        }
        else {
            if ((*pos)->val > val) pos = &((*pos)->left);
            else pos = &((*pos)->right);
        }
    }

    return root;
}