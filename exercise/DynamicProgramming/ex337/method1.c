/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#define max(a, b) ((a) > (b) ? (a) : (b))

struct SubtreeStatus {
    int selected;
    int notSelected;
};

struct SubtreeStatus dfs(struct TreeNode* node) {
    if (!node) return (struct SubtreeStatus){0, 0};

    struct SubtreeStatus l = dfs(node->left);
    struct SubtreeStatus r = dfs(node->right);

    int selected = node->val + l.notSelected + r.notSelected;
    int notSelected = max(l.selected, l.notSelected) + max(r.selected, r.notSelected);

    return (struct SubtreeStatus){selected, notSelected};
}

int rob(struct TreeNode* root) {
    struct SubtreeStatus rootStatus = dfs(root);
    return max(rootStatus.selected, rootStatus.notSelected);
}