/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* constructMaximumBinaryTree(int* nums, int numsSize) {
    if (numsSize == 0) return NULL;

    int index = 0, max = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > max) {
            max = nums[i];
            index = i;
        }
    }

    struct TreeNode* root = malloc(sizeof(struct TreeNode));
    root->val = max;

    struct TreeNode* left = constructMaximumBinaryTree(nums, index);
    struct TreeNode* right = constructMaximumBinaryTree(nums + index + 1, numsSize - index - 1);

    root->left = left;
    root->right = right;

    return root;
}