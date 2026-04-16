/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int maxDepth(struct TreeNode* root) {
    if(root == NULL) return 0;
		
		// 多余工作，降低效率
    // if(root->left == NULL && root->right == NULL) return 1;
    // if(root->left == NULL && root->right != NULL) return maxDepth(root->right) + 1;
    // if(root->left != NULL && root->right == NULL) return maxDepth(root->left) + 1;
    
		int left_depth = maxDepth(root->left);
    int right_depth = maxDepth(root->right);
    if(left_depth >= right_depth) return left_depth + 1;
    else return right_depth + 1;
}