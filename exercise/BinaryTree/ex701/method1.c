/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* insert(struct TreeNode** root, int val) {
    if ((*root) == NULL) {
        (*root) = malloc(sizeof(struct TreeNode));
        (*root)->val = val;
				// 内存未初始化问题：
				// 这里初始化 left, right 为 NULL 的是必要的，测试时树会被遍历，从而访问到新节点的左右指针，不初始化会访问到非法地址
				// 同时也应该养成初始化的习惯
        (*root)->left = NULL;
        (*root)->right = NULL;
        return *root;
    }
    if ((*root)->val > val) (*root)->left = insert(&((*root)->left), val);
    else (*root)->right = insert(&((*root)->right), val);

    return *root;
}

struct TreeNode* insertIntoBST(struct TreeNode* root, int val) {
    return insert(&root, val);
}