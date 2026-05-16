/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int minDepth(struct TreeNode* root) {
    if(root == NULL) return 0;

    int left_min = minDepth(root->left);
    int right_min = minDepth(root->right);
    
    if(left_min == 0 && right_min == 0) return 1;
    else if(left_min == 0 && right_min > 0) return right_min + 1;
    else if(left_min > 0 && right_min == 0) return left_min + 1;
    else if(left_min >= right_min) return right_min + 1;
    else return left_min + 1;
}