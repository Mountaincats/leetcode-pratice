/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool dfs(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q,struct TreeNode** ans) {
    if (root == NULL) return false;
    bool lson = dfs(root->left, p, q, ans);
    bool rson = dfs(root->right, p, q, ans);

    if ((lson && rson) || ((root->val == p->val || root->val == q->val) && (lson || rson))) *ans = root;
    return lson || rson || root->val == p->val || root->val == q->val;
}

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    struct TreeNode* ans = root;
    dfs(root, p, q, &ans);
    return ans;
}