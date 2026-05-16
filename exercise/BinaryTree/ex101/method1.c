/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool compare(struct TreeNode* t1, struct TreeNode* t2) {
    if(t1 == NULL && t2 != NULL || t1 != NULL && t2 == NULL) return false;
    if(t1 == NULL && t2 == NULL) return true;

    if(t1->val == t2->val) {
        if(!compare(t1->left, t2->right)) return false;
        if(!compare(t1->right, t2->left)) return false;
        return true;
    }

    return false;
}

bool isSymmetric(struct TreeNode* root) {
    if(root == NULL || root->left == NULL && root->right == NULL) return true;

    return compare(root->left, root->right);
}
