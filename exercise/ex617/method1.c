/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

// 此方法新生成的树会有节点指针指向 root1, root2 中的节点，不是全部分配新的空间，但题目没要求

struct TreeNode* merge(struct TreeNode* root1, struct TreeNode* root2) {
    if (root1 == NULL) {
        return root2;
    }
    if (root2 == NULL) {
        return root1;
    }

    struct TreeNode* root = malloc(sizeof(struct TreeNode));

    // if (root1 == NULL && root2 == NULL) return NULL;

    // struct TreeNode* root = malloc(sizeof(struct TreeNode));
    // if (root2 == NULL) {
    //     root->val = root1->val;
    //     root->left = merge(root1->left, NULL);
    //     root->right = merge(root1->right, NULL);
    //     return root;
    // }
    // if (root1 == NULL) {
    //     root->val = root2->val;
    //     root->left = merge(NULL, root2->left);
    //     root->right = merge(NULL, root2->right);
    //     return root;
    // }

    root->val = root1->val + root2->val;
    root->left = merge(root1->left, root2->left);
    root->right = merge(root1->right, root2->right);

    return root;
}

struct TreeNode* mergeTrees(struct TreeNode* root1, struct TreeNode* root2) {
    return merge(root1, root2);
}