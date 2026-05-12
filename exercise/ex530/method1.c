/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void dfs(struct TreeNode* root, int* pre, int* ans) {
    if (root == NULL) return;

    dfs(root->left, pre, ans);

    if (*pre != -1) {
        int abs = root->val - *pre;
        if (abs < *ans) *ans = abs;
    }
    *pre = root->val;

    dfs(root->right, pre, ans);
}

int getMinimumDifference(struct TreeNode* root) {
    int ans = INT_MAX, pre = -1;
    dfs(root, &pre, &ans);
    return ans;
}