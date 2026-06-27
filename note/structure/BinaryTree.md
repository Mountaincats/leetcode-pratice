## 二叉树
[TOC]

### 一、主要操作
- 前、中、后、层序遍历
- 查找、插入、删除节点
- 二叉树线索化
- 平衡化

---

### 二、遍历

二叉树遍历的核心问题是**访问节点的顺序**。根据根节点被访问的时机，分为前序、中序、后序遍历；层序遍历则按层级从上到下、从左到右访问。

- **前序遍历（Preorder）**：根 -> 左 -> 右
- **中序遍历（Inorder）**：左 -> 根 -> 右
- **后序遍历（Postorder）**：左 -> 右 -> 根
- **层序遍历（Level Order）**：从上到下、从左到右逐层访问


#### (1) 前序遍历

**1. 基本原理**

前序遍历的顺序是：**先访问当前节点，再遍历左子树，最后遍历右子树**。递归定义非常直观，迭代和 Morris 遍历则需要显式维护访问顺序。

**2. 递归写法**

```c
void preorder(TreeNode* root, int* res, int* returnSize) {
    if (!root) return;
    res[(*returnSize)++] = root->val;   // 访问根
    preorder(root->left, res, returnSize);
    preorder(root->right, res, returnSize);
}
```

- 代码最简洁，逻辑与定义完全一致
- 隐式使用系统调用栈，空间复杂度 $O(h)$，$h$ 为树高

**3. 迭代写法（显式栈）**

```c
int* preorderTraversal(TreeNode* root, int* returnSize) {
    int* res = malloc(sizeof(int) * 100);
    *returnSize = 0;
    if (!root) return res;

    TreeNode* stack[100];
    int top = -1;
    stack[++top] = root;

    while (top >= 0) {
        TreeNode* cur = stack[top--];
        res[(*returnSize)++] = cur->val;    // 访问根

        // 先压右孩子，再压左孩子，保证出栈时左先于右
        if (cur->right) stack[++top] = cur->right;
        if (cur->left) stack[++top] = cur->left;
    }
    return res;
}
```

- 用显式栈模拟递归
- 入栈顺序与访问顺序相反，因此右孩子先入栈

**4. Morris 遍历**

```c
int* preorderTraversal(TreeNode* root, int* returnSize) {
    int* res = malloc(sizeof(int) * 100);
    *returnSize = 0;
    TreeNode* cur = root;

    while (cur) {
        if (!cur->left) {
            res[(*returnSize)++] = cur->val;
            cur = cur->right;
        } else {
            // 找到左子树中最右的节点（前驱）
            TreeNode* pre = cur->left;
            while (pre->right && pre->right != cur) {
                pre = pre->right;
            }

            if (!pre->right) {
                // 第一次到达 cur，建立线索
                res[(*returnSize)++] = cur->val;  // 前序：此时访问
                pre->right = cur;
                cur = cur->left;
            } else {
                // 第二次到达 cur，拆除线索
                pre->right = NULL;
                cur = cur->right;
            }
        }
    }
    return res;
}
```

- 不使用栈，空间复杂度 $O(1)$
- 通过临时线索回到父节点，遍历完成后恢复原树结构
- **前序的关键点**：在第一次到达节点时就访问它


#### (2) 中序遍历

**1. 基本原理**

中序遍历的顺序是：**先遍历左子树，再访问当前节点，最后遍历右子树**。对二叉搜索树（BST）而言，中序遍历的结果是有序序列。

**2. 递归写法**

```c
void inorder(TreeNode* root, int* res, int* returnSize) {
    if (!root) return;
    inorder(root->left, res, returnSize);
    res[(*returnSize)++] = root->val;      // 访问根
    inorder(root->right, res, returnSize);
}
```

**3. 迭代写法（显式栈）**

```c
int* inorderTraversal(TreeNode* root, int* returnSize) {
    int* res = malloc(sizeof(int) * 100);
    *returnSize = 0;
    TreeNode* stack[100];
    int top = -1;
    TreeNode* cur = root;

    while (cur || top >= 0) {
        // 一路向左
        while (cur) {
            stack[++top] = cur;
            cur = cur->left;
        }
        cur = stack[top--];
        res[(*returnSize)++] = cur->val;    // 访问根
        cur = cur->right;
    }
    return res;
}
```

- 栈中保存的是"待访问根的节点"
- 每弹出一个节点，就访问它，然后转向右子树

**4. Morris 遍历**

```c
int* inorderTraversal(TreeNode* root, int* returnSize) {
    int* res = malloc(sizeof(int) * 100);
    *returnSize = 0;
    TreeNode* cur = root;

    while (cur) {
        if (!cur->left) {
            res[(*returnSize)++] = cur->val;
            cur = cur->right;
        } else {
            // 找到左子树中最右的节点
            TreeNode* pre = cur->left;
            while (pre->right && pre->right != cur) {
                pre = pre->right;
            }

            if (!pre->right) {
                // 第一次到达 cur，建立线索
                pre->right = cur;
                cur = cur->left;
            } else {
                // 第二次到达 cur，拆除线索并访问
                pre->right = NULL;
                res[(*returnSize)++] = cur->val;   // 中序：此时访问
                cur = cur->right;
            }
        }
    }
    return res;
}
```

- **中序的关键点**：在第二次回到节点时才访问它
- 同样 $O(1)$ 额外空间


#### (3) 后序遍历

**1. 基本原理**

后序遍历的顺序是：**先遍历左子树，再遍历右子树，最后访问当前节点**。相比前序和中序，后序的迭代写法更复杂，因为必须确认左右子树都访问完才能访问根。

**2. 递归写法**

```c
void postorder(TreeNode* root, int* res, int* returnSize) {
    if (!root) return;
    postorder(root->left, res, returnSize);
    postorder(root->right, res, returnSize);
    res[(*returnSize)++] = root->val;     // 访问根
}
```

**3. 迭代写法（显式栈）**

```c
int* postorderTraversal(TreeNode* root, int* returnSize) {
    int* res = malloc(sizeof(int) * 100);
    *returnSize = 0;
    if (!root) return res;

    TreeNode* stack[100];
    int top = -1;
    TreeNode* cur = root;
    TreeNode* lastVisited = NULL;

    while (cur || top >= 0) {
        // 一路向左
        while (cur) {
            stack[++top] = cur;
            cur = cur->left;
        }

        TreeNode* peek = stack[top];
        // 如果右子树存在且未访问过，则转向右子树
        if (peek->right && lastVisited != peek->right) {
            cur = peek->right;
        } else {
            // 左右都已访问，访问根
            res[(*returnSize)++] = peek->val;
            lastVisited = stack[top--];
        }
    }
    return res;
}
```

- 需要 `lastVisited` 记录上一次访问的节点，以判断右子树是否处理完毕
- 栈顶节点的访问条件是：无右子树，或右子树已访问

**4. Morris 遍历**

```c
int* postorderTraversal(TreeNode* root, int* returnSize) {
    int* res = malloc(sizeof(int) * 100);
    *returnSize = 0;
    TreeNode* dummy = malloc(sizeof(TreeNode));
    dummy->left = root;
    dummy->right = NULL;
    TreeNode* cur = dummy;

    while (cur) {
        if (!cur->left) {
            cur = cur->right;
        } else {
            TreeNode* pre = cur->left;
            while (pre->right && pre->right != cur) {
                pre = pre->right;
            }

            if (!pre->right) {
                pre->right = cur;
                cur = cur->left;
            } else {
                // 逆序输出 cur->left 到 pre 的路径（左子树的右链）
                TreeNode* start = cur->left;
                int count = 0;
                while (start != cur) {
                    res[(*returnSize) + count] = start->val;
                    start = start->right;
                    count++;
                }
                for (int i = 0; i < count / 2; i++) {
                    int tmp = res[*returnSize + i];
                    res[*returnSize + i] = res[*returnSize + count - 1 - i];
                    res[*returnSize + count - 1 - i] = tmp;
                }
                *returnSize += count;

                pre->right = NULL;
                cur = cur->right;
            }
        }
    }
    free(dummy);
    return res;
}
```

- 后序 Morris 是最复杂的：需要在第二次回到节点时**逆序输出左子树的右链**
- 实际工程中较少手写，但面试常问原理


#### (4) 层序遍历

**1. 基本原理**

层序遍历按**层级从上到下、每层从左到右**依次访问节点。本质是 **BFS（广度优先搜索）**，使用队列维护待访问节点。

**2. 代码实现（队列）**

```c
int** levelOrder(TreeNode* root, int* returnSize, int** returnColumnSizes) {
    if (!root) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    int** res = malloc(sizeof(int*) * 2000);
    *returnColumnSizes = malloc(sizeof(int) * 2000);
    *returnSize = 0;

    TreeNode* queue[2000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        int levelSize = rear - front;
        (*returnColumnSizes)[*returnSize] = levelSize;
        res[*returnSize] = malloc(sizeof(int) * levelSize);

        for (int i = 0; i < levelSize; i++) {
            TreeNode* cur = queue[front++];
            res[*returnSize][i] = cur->val;

            if (cur->left) queue[rear++] = cur->left;
            if (cur->right) queue[rear++] = cur->right;
        }
        (*returnSize)++;
    }
    return res;
}
```

- 每一轮循环处理一整层节点
- 时间复杂度 $O(n)$，空间复杂度 $O(w)$，$w$ 为最大宽度
- 层序遍历是**唯一不需要区分递归/迭代/Morris** 的遍历方式（队列 BFS 是标准解法）

---

### 三、平衡化

平衡化的目标是在动态插入、删除节点的过程中，**控制树的高度为 $O(\log n)$**，从而保证查找、插入、删除等操作的时间复杂度稳定在 $O(\log n)$。

常见的自平衡二叉树包括 **AVL 树** 和 **红黑树**，二者核心思想都是：在每次插入或删除后，通过旋转操作修复失衡。

- AVL 树：严格平衡，查询更快，维护成本更高
- 红黑树：近似平衡，插入删除开销更小，工程中使用更广泛（如 C++ `std::map`）


#### (1) 失衡类型与旋转

**1. 基本概念**

- **平衡因子（Balance Factor）**：`BF = 左子树高度 - 右子树高度`
- AVL 树要求所有节点的 $|BF| \le 1$，否则需要旋转调整

**2. 四种失衡类型**

设最低失衡节点为 $A$：

| 类型 | 描述 | 示意图 |
|----|----|----|
| LL | $A$ 的左孩子的左子树过高 | `A←B←C` |
| RR | $A$ 的右孩子的右子树过高 | `A->B->C` |
| LR | $A$ 的左孩子的右子树过高 | `A←B->C` |
| RL | $A$ 的右孩子的左子树过高 | `A->B←C` |

**3. 旋转操作**

- **右旋（Right Rotation）**：解决 LL 型失衡

```
    A                B
   / \              / \
  B   Ar   ->      Bl  A
 / \                  / \
Bl  Br               Br  Ar
```

```c
TreeNode* rightRotate(TreeNode* A) {
    TreeNode* B = A->left;
    TreeNode* Br = B->right;

    B->right = A;
    A->left = Br;

    // 更新高度（若维护了高度字段）
    return B;
}
```

- **左旋（Left Rotation）**：解决 RR 型失衡

```
    A                B
   / \              / \
  Al  B    ->      A   Br
     / \          / \ 
    Bl  Br       Al  Bl
```

```c
TreeNode* leftRotate(TreeNode* A) {
    TreeNode* B = A->right;
    TreeNode* Bl = B->left;

    B->left = A;
    A->right = Bl;

    // 更新高度
    return B;
}
```

- **LR 型**：先对 $B$ 左旋，再对 $A$ 右旋
- **RL 型**：先对 $B$ 右旋，再对 $A$ 左旋

```c
// LR: 先左旋 B，再右旋 A
A->left = leftRotate(B);
A = rightRotate(A);

// RL: 先右旋 B，再左旋 A
A->right = rightRotate(B);
A = leftRotate(A);
```


#### (2) AVL 树的插入与删除

**1. 插入流程**

- 按 BST 规则插入新节点
- **自底向上**更新各祖先节点的高度
- 检查每个节点的平衡因子，发现失衡则执行对应旋转
- 旋转后该子树高度恢复，无需继续向上检查

**关键点**：插入只会引起**一条路径上的失衡**，旋转最多两次即可修复。

**2. 删除流程**

- 按 BST 规则删除节点（删除逻辑与普通 BST 相同）
- 自底向上更新高度并检查平衡因子
- 每修复一个失衡节点后，仍需继续向上检查
- 删除可能引起**多条路径上的失衡**，最坏情况下需要 $O(\log n)$ 次旋转

**3. 插入代码示例（带高度维护）**

```c
typedef struct TreeNode {
    int val;
    int height;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

int height(TreeNode* node) {
    return node ? node->height : 0;
}

int getBalance(TreeNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

TreeNode* insert(TreeNode* node, int val) {
    // 1. 普通 BST 插入
    if (!node) {
        TreeNode* newNode = malloc(sizeof(TreeNode));
        newNode->val = val;
        newNode->height = 1;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (val < node->val)
        node->left = insert(node->left, val);
    else if (val > node->val)
        node->right = insert(node->right, val);
    else
        return node;   // 不插入重复值

    // 2. 更新高度
    node->height = 1 + (height(node->left) > height(node->right)
                        ? height(node->left) : height(node->right));

    // 3. 检查平衡并旋转
    int balance = getBalance(node);

    // LL
    if (balance > 1 && val < node->left->val)
        return rightRotate(node);

    // RR
    if (balance < -1 && val > node->right->val)
        return leftRotate(node);

    // LR
    if (balance > 1 && val > node->left->val) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL
    if (balance < -1 && val < node->right->val) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}
```


#### (3) 红黑树

**1. 五大性质**

1. 每个节点是红色或黑色
2. 根节点是黑色
3. 所有叶子节点（NIL）是黑色
4. **红色节点不能有红色子节点**（不存在连续红节点）
5. 从任一节点到其所有后代 NIL 节点的路径上，**黑色节点数量相同**

性质 4 和 5 共同保证了：红黑树的最长路径不超过最短路径的两倍，即**近似平衡**。

**2. 与 AVL 树的对比**

| 特性 | AVL 树 | 红黑树 |
|----|----|----|
| 平衡程度 | 严格平衡 | 近似平衡 |
| 查询性能 | 略快（$h \approx \log n$） | 略慢（最长路径约 $2\log n$） |
| 插入旋转次数 | 最多 2 次 | 最多 2 次（但触发概率更低） |
| 删除旋转次数 | $O(\log n)$ | $O(1)$（均摊） |
| 典型应用 | 查询密集型场景 | 通用容器（`std::map`、`HashMap`） |

**3. 核心操作思想**

- **插入**：先按 BST 插入，新节点染红，然后通过**重新着色**和**旋转**修复红黑性质
- **删除**：比 AVL 更复杂，涉及"双重黑色"概念，但最终可通过有限次旋转和重着色修复

红黑树的完整实现较长，面试中通常只要求掌握**思想**和**与 AVL 的区别**，不要求手撸全量代码。


#### (4) 平衡化总结

| 操作 | AVL 树 | 红黑树 |
|----|----|----|
| 插入 | 最多旋转 2 次，自底向上修复 | 最多旋转 2 次，重着色为主 |
| 删除 | 可能多次旋转，向上传播修复 | 均摊 $O(1)$ 旋转，局部修复 |
| 高度 | $O(\log n)$，常数更小 | $O(\log n)$，常数略大 |
| 工程选择 | 读多写少 | 读写均衡或写多 |

### 四、查找、插入、删除节点

二叉树的查找、插入、删除操作，**普通二叉树**和**二叉搜索树**差异很大。普通二叉树没有有序性约束，只能通过遍历完成；而 BST 利用其有序性，可以将单步操作的时间复杂度降至 $O(\log n)$（平衡情况下）。

本节以 **二叉搜索树** 为核心展开。


#### (1) 查找节点

**1. 基本原理**

BST 的性质：
- 左子树所有节点值 `<` 当前节点值
- 右子树所有节点值 `>` 当前节点值

查找时，从根节点开始比较：
- 等于目标值 -> 返回该节点
- 小于目标值 -> 进入左子树
- 大于目标值 -> 进入右子树
- 遇到空节点 -> 查找失败

**2. 递归写法**

```c
TreeNode* search(TreeNode* root, int target) {
    if (!root || root->val == target)
        return root;
    
    if (target < root->val)
        return search(root->left, target);
    else
        return search(root->right, target);
}
```

- 代码简洁，逻辑直观
- 隐式使用递归栈，空间复杂度 $O(h)$

**3. 迭代写法**

```c
TreeNode* search(TreeNode* root, int target) {
    TreeNode* cur = root;
    while (cur) {
        if (cur->val == target)
            return cur;
        else if (target < cur->val)
            cur = cur->left;
        else
            cur = cur->right;
    }
    return NULL;
}
```

- 无递归开销，空间复杂度 $O(1)$
- 工程实践中更常用

**4. 查找最值**

BST 中最小值在最左侧，最大值在最右侧：

```c
// 查找最小节点
TreeNode* findMin(TreeNode* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

// 查找最大节点
TreeNode* findMax(TreeNode* root) {
    while (root && root->right)
        root = root->right;
    return root;
}
```


#### (2) 插入节点

**1. 基本原理**

BST 插入遵循以下规则：
- 从根节点开始，比较插入值与当前节点值
- 小于当前值 -> 往左走；大于当前值 -> 往右走
- 遇到空位置 -> 创建新节点放入

插入的新节点**一定是叶子节点**（除非允许重复值的特殊处理）。

**2. 递归写法**

```c
TreeNode* insert(TreeNode* root, int val) {
    if (!root) {
        TreeNode* newNode = malloc(sizeof(TreeNode));
        newNode->val = val;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (val < root->val)
        root->left = insert(root->left, val);
    else if (val > root->val)
        root->right = insert(root->right, val);
    // 相等时不插入（也可改为计数或允许重复）

    return root;
}
```

- 递归回溯时自动维护父子关系
- 时间复杂度 $O(h)$，平衡时 $O(\log n)$，退化时 $O(n)$

**3. 迭代写法**

```c
TreeNode* insert(TreeNode* root, int val) {
    TreeNode* newNode = malloc(sizeof(TreeNode));
    newNode->val = val;
    newNode->left = newNode->right = NULL;

    if (!root) return newNode;

    TreeNode* cur = root;
    TreeNode* parent = NULL;

    while (cur) {
        parent = cur;
        if (val < cur->val)
            cur = cur->left;
        else if (val > cur->val)
            cur = cur->right;
        else {
            // 重复值，直接释放并返回原树
            free(newNode);
            return root;
        }
    }

    if (val < parent->val)
        parent->left = newNode;
    else
        parent->right = newNode;

    return root;
}
```

- 需要维护 `parent` 指针，找到插入位置后挂接
- 空间复杂度 $O(1)$


#### (3) 删除节点

**1. 基本原理**

BST 删除是三种操作中最复杂的，需要分三种情况讨论：

| 情况 | 描述 | 处理方式 |
|----|----|----|
| 叶子节点 | 无左右子树 | 直接删除，父节点对应指针置 NULL |
| 只有一个子树 | 仅有左或右子树 | 用子树根节点替换被删节点 |
| 有两个子树 | 左右子树都存在 | 用**中序后继**（或前驱）替换，再删除后继 |

**2. 中序后继与前驱**

- **中序后继**：右子树中的最小值（最左节点）
- **中序前驱**：左子树中的最大值（最右节点）

两种方式等价，工程中通常用后继更常见。

**3. 递归删除**

```c
// 查找最小节点（用于找中序后继）
TreeNode* findMin(TreeNode* root) {
    while (root->left)
        root = root->left;
    return root;
}

TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return NULL;

    if (key < root->val) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->val) {
        root->right = deleteNode(root->right, key);
    }
    else {
        // 找到要删除的节点
        // 情况1：叶子节点
        if (!root->left && !root->right) {
            free(root);
            return NULL;
        }
        // 情况2：只有一个子树
        else if (!root->left) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (!root->right) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        // 情况3：有两个子树
        else {
            // 找到中序后继（右子树最小值）
            TreeNode* successor = findMin(root->right);
            // 用后继值替换当前节点
            root->val = successor->val;
            // 删除后继节点
            root->right = deleteNode(root->right, successor->val);
        }
    }
    return root;
}
```

**4. 三种情况的图示**

```
情况1：叶子节点          情况2：只有右子树        情况3：左右都有
     5                        5                       5
    / \                      / \                     / \
   3   7                    3   7                  3   7
      /                           \               /   / \
     6                             8            2   6   8
删除 3 -> 直接移除       删除 7 -> 用 8 替换     删除 5 -> 用 6 替换，再删除原 6
```

**5. 迭代删除**

迭代删除需要维护 `parent` 指针，同时处理三种情况，代码量较大。核心难点在于：
- 找到待删节点及其父节点
- 处理"有两个子树"时，还需要找到后继节点及其父节点

面试中**递归版本已经足够**，迭代版本了解思路即可。


#### (4) 操作复杂度分析

| 操作 | 平均情况（平衡 BST） | 最坏情况（退化成链） |
|----|-----------------|---------------|
| 查找 | $O(\log n)$ | $O(n)$ |
| 插入 | $O(\log n)$ | $O(n)$ |
| 删除 | $O(\log n)$ | $O(n)$ |

**关键结论**：普通 BST 在有序数据插入时会退化成链表，因此**必须配合平衡化机制**（AVL / 红黑树）才能保证性能。


#### (5) 允许重复值的处理策略

| 策略 | 做法 | 影响 |
|----|----|----|
| 禁止重复 | 插入时忽略或等于时返回 | 简单，但无法统计频次 |
| 左子树存储 | 重复值插入左子树 | 查找、删除需注意 |
| 右子树存储 | 重复值插入右子树 | 同上 |
| 计数域 | 节点增加 `count` 字段 | 最优雅，删除时 count-- 即可 |

计数域示例：
```c
typedef struct TreeNode {
    int val;
    int count;          // 出现次数
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;
```

---

### 五、二叉树线索化

普通二叉树中有大量空指针：`n` 个节点的二叉树有 `n+1` 个空指针域（左/右孩子为空）。线索化的核心思想是**利用这些空指针，指向遍历序列中的前驱或后继节点**，从而在不借助栈、递归或队列的情况下完成遍历。


#### (1) 基本原理

**1. 线索的定义**

对二叉树中的每个节点：
- 若左指针为空 -> 指向该节点在中序遍历中的**前驱**
- 若右指针为空 -> 指向该节点在中序遍历中的**后继**

为了区分指针是指向"真实孩子"还是"线索"，需要增加两个标志位：

```c
typedef struct ThreadNode {
    int val;
    struct ThreadNode* left;
    struct ThreadNode* right;
    int ltag;   // 0: left 指向左孩子; 1: left 指向前驱
    int rtag;   // 0: right 指向右孩子; 1: right 指向后继
} ThreadNode;
```

**2. 通常使用中序线索化**
中序线索化是**绝对主流**，下文以中序为例。

| 线索化方式 | 使用频率 | 原因 |
|---------|--------|------|
| 中序线索化 | 高 | BST 中序有序，线索化后支持高效前驱/后继查询 |
| 前序线索化 | 中 | 前序遍历顺序固定，但应用场景较少 |
| 后序线索化 | 低 | 后序复杂，且难以从线索反推父节点 |



#### (2) 线索化过程

**1. 核心思路**

在线索化过程中，用一个指针 `prev` 始终指向**刚刚访问过的节点**（即当前节点的中序前驱）：
- 如果当前节点 `cur->left == NULL`，则 `cur->left = prev`（指向前驱），并设置 `ltag = 1`
- 如果 `prev != NULL` 且 `prev->right == NULL`，则 `prev->right = cur`（指向后继），并设置 `rtag = 1`

**2. 递归线索化代码**

```c
ThreadNode* prev = NULL;   // 全局或传入指针

void inorderThreading(ThreadNode* cur) {
    if (!cur) return;

    // 处理左子树
    inorderThreading(cur->left);

    // ===== 处理当前节点 =====
    // 左指针为空 -> 指向前驱
    if (!cur->left) {
        cur->left = prev;
        cur->ltag = 1;
    }

    // 前驱的右指针为空 -> 指向当前节点（后继）
    if (prev && !prev->right) {
        prev->right = cur;
        prev->rtag = 1;
    }

    prev = cur;   // 更新前驱
    // =========================

    // 处理右子树（注意：如果 rtaged=1，不能继续深入）
    inorderThreading(cur->right);
}
```

**3. 添加头结点（哑元节点）**

为了方便遍历，通常引入一个**头结点** `head`：
- `head->left` 指向二叉树的根（若有）
- `head->right` 指向中序遍历的最后一个节点
- 第一个节点的 `left` 指向 `head`
- 最后一个节点的 `right` 指向 `head`

形成**双向循环线索链表**，遍历更加统一。

```c
ThreadNode* createThreadTree(ThreadNode* root) {
    ThreadNode* head = malloc(sizeof(ThreadNode));
    head->ltag = 0;
    head->rtag = 1;
    head->right = head;   // 初始指向自己

    if (!root) {
        head->left = head;
    } else {
        head->left = root;
        prev = head;                 // 前驱初始化为 head
        inorderThreading(root);
        // 收尾：最后一个节点的 right 指向 head
        prev->right = head;
        prev->rtag = 1;
        head->right = prev;          // head->right 指向最后一个节点
    }
    return head;
}
```


#### (3) 线索二叉树上的遍历

**1. 中序遍历（无栈、无递归）**

```c
void threadInorder(ThreadNode* head) {
    ThreadNode* cur = head->left;   // cur 指向根

    while (cur != head) {
        // 找到最左节点（第一个要访问的）
        while (cur->ltag == 0) {
            cur = cur->left;
        }

        // 访问当前节点
        printf("%d ", cur->val);

        // 沿着线索向右走
        while (cur->rtag == 1 && cur->right != head) {
            cur = cur->right;
            printf("%d ", cur->val);
        }

        // 跳到右子树
        cur = cur->right;
    }
}
```

- 完全不需要栈或递归
- 时间复杂度 $O(n)$，空间复杂度 $O(1)$
- 这是线索化的核心价值所在

**2. 查找中序后继**

```c
// 找 cur 的中序后继
ThreadNode* next(ThreadNode* cur) {
    // 如果有右子树（rtag=0），后继是右子树的最左节点
    if (cur->rtag == 0) {
        ThreadNode* p = cur->right;
        while (p->ltag == 0) {
            p = p->left;
        }
        return p;
    }
    // 否则直接走线索
    else {
        return cur->right;
    }
}
```

**3. 查找中序前驱**

```c
// 找 cur 的中序前驱
ThreadNode* prevNode(ThreadNode* cur) {
    // 如果有左子树（ltag=0），前驱是左子树的最右节点
    if (cur->ltag == 0) {
        ThreadNode* p = cur->left;
        while (p->rtag == 0) {
            p = p->right;
        }
        return p;
    }
    // 否则直接走线索
    else {
        return cur->left;
    }
}
```


#### (4) 插入与删除

线索二叉树上的插入和删除**比较复杂**，因为：
- 插入/删除会破坏原有的线索关系
- 需要重新线索化受影响的子树，或精细地修复线索

工程中通常的处理方式：
- **简单方案**：修改后整体重新线索化（适用于静态或低频修改的场景）
- **复杂方案**：局部修复线索（实现复杂，面试一般不要求）

这也是线索二叉树**主要用于静态或只读场景**的原因。


#### (5) 线索化 vs Morris 遍历

| 对比项 | 线索二叉树 | Morris 遍历 |
|------|----------|------------|
| 空间复杂度 | $O(1)$（预建线索） | $O(1)$（临时建线索） |
| 预处理 | 需要一次性线索化 | 遍历时临时建线索 |
| 树结构 | 永久修改（增加 tag） | 遍历后恢复原结构 |
| 适用场景 | 频繁遍历、查询前驱后继 | 单次遍历、不想改结构 |
| 代码复杂度 | 中等 | 较高 |

**核心区别**：线索二叉树是**数据结构层面的改造**，Morris 遍历是**算法层面的技巧**。


#### (6) 小结

| 特性 | 说明 |
|----|----|
| 目的 | 利用空指针存储遍历线索，实现 $O(1)$ 空间遍历 |
| 核心 | 中序线索化最常用，配合 tag 区分孩子/线索 |
| 优势 | 无栈无递归遍历，支持高效前驱/后继查询 |
| 劣势 | 插入删除复杂，结构被永久修改 |
| 典型应用 | 数据库索引、静态符号表、频繁遍历场景 |

