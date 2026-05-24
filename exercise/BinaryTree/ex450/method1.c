/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    struct TreeNode *pre = NULL, *cur = root;
    struct TreeNode *left = NULL, *right = NULL;
    bool is_left;

    while (true) {
        if (cur == NULL) return root;
        else {
            if (cur->val == key) {
                left = cur->left;
                right = cur->right;
                free(cur);
                break;
            }
            else if (cur->val > key) {
                pre = cur;
                cur = cur->left;
                is_left = true;
            }
            else {
                pre = cur;
                cur = cur->right;
                is_left = false;
            }
        }
    }

    struct TreeNode* tmp = right;
    if (tmp == NULL) {
        tmp = left;
    }
    else {
        while (right->left != NULL) {
            right = right->left;
        }
        right->left = left;
    }

    if (pre == NULL) return tmp;
    else {
        if (is_left) pre->left = tmp;
        else pre->right = tmp;
        return root;
    }
}