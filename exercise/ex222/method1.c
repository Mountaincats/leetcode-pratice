/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

// 判断完全二叉树的最右叶节点的深度是否等于 depth
bool check_right_depth(struct TreeNode* root, int depth) {
    if (root == NULL) return false;
    while (root->right != NULL) {
        root = root->right;
        depth--;
    }
    if (depth != 0) return false;
    else return true;
}

int countNodes(struct TreeNode* root) {
    if (root == NULL)  return 0;
    else if (root->left == NULL) return 1;

    struct TreeNode* temp = root;
    int depth = 0;
    int node_num = 0;
    int node_depth_num = 1;

		// 计算深度，最下层的节点最大数量，除最下层的节点数
    do {
        temp = temp->left;
        depth++;
        node_num = node_num * 2 + 1;
        node_depth_num *= 2;
    } while (temp->left != NULL);

		// 判断是否是满二叉树
    temp = root;
    int depth_right = 0;
    while (temp->right != NULL) {
        temp = temp->right;
        depth_right++;
    }
    
    if (depth == depth_right) {
        node_num += node_depth_num;
        return node_num;
    }

		// 如不是满二叉树则计算最下层的节点数
    temp = root;
    do {
        node_depth_num /= 2;
        bool equal_depth = check_right_depth(temp->left, --depth);

        if (equal_depth) {
            node_num += node_depth_num;
            temp = temp->right;
        } else {
            temp = temp->left;
        }
    } while (node_depth_num != 1);

    return node_num;
}