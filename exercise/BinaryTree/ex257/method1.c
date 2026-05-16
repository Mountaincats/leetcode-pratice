/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void backtrack(struct TreeNode* root, int* returnSize, int* path, int depth, char** solutions) {
    if (root->left == NULL && root->right == NULL) {
        path[depth] = root->val;

        char* tmp = malloc(sizeof(char) * 600);
        tmp[0] = '\0';

        char num[5];
        for (int i = 0; i < depth; i++) {
            sprintf(num, "%d", path[i]);
            strcat(tmp, num);
            strcat(tmp, "->");
        }
        sprintf(num, "%d", path[depth]);
        strcat(tmp, num);

        solutions[(*returnSize)++] = tmp;
        
        return;
    }
    else {
        path[depth] = root->val;
        if (root->left != NULL) backtrack(root->left, returnSize, path, depth + 1, solutions);
        if (root->right != NULL) backtrack(root->right, returnSize, path, depth + 1, solutions);
        return;
    }
}

char** binaryTreePaths(struct TreeNode* root, int* returnSize) {
    char** solutions = malloc(sizeof(char*) * 50);
    *returnSize = 0;

    if (root != NULL) {
        int* path = malloc(sizeof(int) * 100);
        backtrack(root, returnSize, path, 0, solutions);
        free(path);
    }

    return solutions;
}