/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

// 父节点哈希表结构
typedef struct ParentMap {
    int key;                    // 节点值
    struct TreeNode* value;     // 父节点指针
    UT_hash_handle hh;          // uthash需要的句柄
} ParentMap;

// 访问标记哈希表结构
typedef struct VisitedMap {
    int key;                    // 节点值
    int visited;                // 访问标记
    UT_hash_handle hh;          // uthash需要的句柄
} VisitedMap;

// 递归记录每个节点的父节点
void dfs(struct TreeNode* root, ParentMap** parent_map) {
    if (root->left != NULL) {
        // 添加左子节点到父节点的映射
        ParentMap* item = (ParentMap*)malloc(sizeof(ParentMap));
        item->key = root->left->val;
        item->value = root;
        HASH_ADD_INT(*parent_map, key, item);
        dfs(root->left, parent_map);
    }
    if (root->right != NULL) {
        // 添加右子节点到父节点的映射
        ParentMap* item = (ParentMap*)malloc(sizeof(ParentMap));
        item->key = root->right->val;
        item->value = root;
        HASH_ADD_INT(*parent_map, key, item);
        dfs(root->right, parent_map);
    }
}

// 释放父节点哈希表内存
void free_parent_map(ParentMap** parent_map) {
    ParentMap *current, *tmp;
    HASH_ITER(hh, *parent_map, current, tmp) {
        HASH_DEL(*parent_map, current);
        free(current);
    }
}

// 释放访问标记哈希表内存
void free_visited_map(VisitedMap** visited_map) {
    VisitedMap *current, *tmp;
    HASH_ITER(hh, *visited_map, current, tmp) {
        HASH_DEL(*visited_map, current);
        free(current);
    }
}

// 寻找最近公共祖先
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, 
                                     struct TreeNode* p, 
                                     struct TreeNode* q) {
    if (root == NULL || p == NULL || q == NULL) {
        return NULL;
    }
    
    // 初始化哈希表
    ParentMap* parent_map = NULL;
    VisitedMap* visited_map = NULL;
    
    // 为根节点添加映射（根节点的父节点为NULL）
    ParentMap* root_item = (ParentMap*)malloc(sizeof(ParentMap));
    root_item->key = root->val;
    root_item->value = NULL;
    HASH_ADD_INT(parent_map, key, root_item);
    
    // 递归记录所有节点的父节点
    dfs(root, &parent_map);
    
    // 从p节点向上标记所有祖先
    struct TreeNode* current = p;
    while (current != NULL) {
        // 在哈希表中标记当前节点
        VisitedMap* visited_item = (VisitedMap*)malloc(sizeof(VisitedMap));
        visited_item->key = current->val;
        visited_item->visited = 1;
        HASH_ADD_INT(visited_map, key, visited_item);
        
        // 向上查找父节点
        ParentMap* parent_item = NULL;
        HASH_FIND_INT(parent_map, &(current->val), parent_item);
        if (parent_item != NULL) {
            current = parent_item->value;
        } else {
            current = NULL;  // 到达根节点
        }
    }
    
    // 从q节点向上查找第一个被标记的祖先
    current = q;
    while (current != NULL) {
        VisitedMap* visited_item = NULL;
        HASH_FIND_INT(visited_map, &(current->val), visited_item);
        if (visited_item != NULL) {
            // 找到公共祖先
            struct TreeNode* result = current;
            
            // 释放哈希表内存
            free_parent_map(&parent_map);
            free_visited_map(&visited_map);
            
            return result;
        }
        
        // 向上查找父节点
        ParentMap* parent_item = NULL;
        HASH_FIND_INT(parent_map, &(current->val), parent_item);
        if (parent_item != NULL) {
            current = parent_item->value;
        } else {
            current = NULL;  // 到达根节点
        }
    }
    
    // 没有找到公共祖先（不会发生，因为根节点一定是公共祖先）
    free_parent_map(&parent_map);
    free_visited_map(&visited_map);
    
    return NULL;
}