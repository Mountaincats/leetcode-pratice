/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void backtrack(struct TreeNode* root, int* num, int* deepest_depth, int depth) {
    if (root->left == NULL && root->right == NULL) {
        if (depth > *deepest_depth) {
            *deepest_depth = depth;
            *num = root->val;
        }
    }
    else {
        if (root->left != NULL) backtrack(root->left, num, deepest_depth, depth + 1);
        if (root->right != NULL) backtrack(root->right, num, deepest_depth, depth + 1);
    }
}

int findBottomLeftValue(struct TreeNode* root) {
    if (root == NULL) return 0;

    int num = 0;
    int deepest_depth = -1;
    backtrack(root, &num, &deepest_depth, 0);

    return num;
}