## 回溯（Backtracking）

### 一、理论

**1. 术语**

> **例题**
> 在二叉树中搜索所有值为 7 的节点，请返回根节点到这些节点的路径，并要求路径中不包含值为 3 的节点。

| 名词 | 定义 | 例题 |
|------|------|------|
| **解（solution）** | 解是满足问题特定条件的答案，可能有一个或多个 | 根节点到节点 7 的满足约束条件的所有路径 |
| **约束条件（constraint）** | 约束条件是问题中限制解的可行性的条件，通常用于剪枝 | 路径中不包含节点 3 |
| **状态（state）** | 状态表示问题在某一时刻的情况，包括已经做出的选择 | 当前已访问的节点路径，即 path 节点列表 |
| **尝试（attempt）** | 尝试是根据可用选择来探索解空间的过程，包括做出选择，更新状态，检查是否为解 | 递归访问左（右）子节点，将节点添加进 path，判断节点的值是否为 7 |
| **回退（backtracking）** | 回退指遇到不满足约束条件的状态时，撤销前面做出的选择，回到上一个状态 | 当越过叶节点、结束节点访问、遇到值为 3 的节点时终止搜索，函数返回 |
| **剪枝（pruning）** | 剪枝是根据问题特性和约束条件避免无意义的搜索路径的方法，可提高搜索效率 | 当遇到值为 3 的节点时，则不再继续搜索 |

---

### 二、模板

```c
/* 判断当前状态是否为解 */
bool isSolution(void)
/* 记录解 */
void recordSolution(void)
/* 判断在当前状态下，该选择是否合法 */
bool isValid(TreeNode *choice)
/* 更新状态 */
void makeChoice(TreeNode *choice)
/* 恢复状态 */
void undoChoice(void)

/* 回溯算法框架 */
void backtrack(State *state, Choice *choices, int numChoices, State *res, int numRes) {
    // 判断是否为解
    if (isSolution(state)) {
        // 记录解
        recordSolution(state, res, numRes);
        // 可能不再继续搜索
        return;
    }
    // 遍历所有选择
    for (int i = 0; i < numChoices; i++) {
        // 剪枝：判断选择是否合法
        if (isValid(state, &choices[i])) {
            // 尝试：做出选择，更新状态
            makeChoice(state, &choices[i]);
            backtrack(state, choices, numChoices, res, numRes);
            // 回退：撤销选择，恢复到之前的状态
            undoChoice(state, &choices[i]);
        }
    }
}
```