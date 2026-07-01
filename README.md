### 一、知识点
下面的专题除索引表、平衡二叉树、B树外都能在 leetcode 上找到对应的习题集，各专题的推荐基础题目可以参考[清单](List.md)。

#### (1) 结构
- **数组(Array)**
- **链表(Linked List)**
- **字符串(String)**
- **栈**
	- 栈(Stack)
	- 单调栈(Monotonic Stack)
- **队列**
	- 队列(Queue)
	- 单调队列(Monotonic Queue)
- **树**
	- 树(Tree)
	- 二叉树(Binary Tree)
	- 二叉搜索树/二叉查找树/二叉排序树(Binary Search Tree, BST)
	- 平衡二叉树
    	- 平衡二叉树(Balanced Tree)
    	- 红黑树(Red-Black Tree)
	- 树状数组/二叉索引树(Fenwick Tree / Binary Indexed Tree)
	- 堆/优先队列(Heap)
	- 线段树(Segment Tree)
	- 字典树(Trie)
	- 并查集/集合(Union Find)
  - B树(B-Tree)
- **哈希表**
  - 哈希表(Hash Table)
  - 哈希函数(Hash Funtion)
- **索引表(Index Table)**
- **有序集合(Sorted Set)**
- **图(Graph)**

#### (2)算法
- **组别一**
  - 二分查找(Binary Search)
  - 排序
    - 排序(Sort)
    - 归并排序(Merge Sort)
    - 计数排序(Counting Sort)
    - 基数排序(Radix Sort)
    - 桶排序(Bucket Sort)
    - 拓扑排序(Topological Sort)
- **组别二**
  - 回溯(Backtracking)
  - 递归(Recursion)
  - 分治(Divide And Conquer)
- **组别三**
  - 双指针(Two Pointers)
  - 滑动窗口(Sliding Window)
  - 前缀和(Prefix Sum)
- **组别四**
  - 广度优先搜索(Breadth First Search, BFS)
  - 深度优先搜索(Depth First Search, DFS)
- **组别五**
  - 贪心(Greedy)
  - 动态规划(Dynamic Programming)
- **组别六**
	- 位运算(Bitwise Operation)
	- 位掩码(Bitmask)

#### (3) 难点专题
- 字符串
- 图
- 回溯
- 递归
- 分治
- 贪心
- 动态规划

---

### 二、leetcode使用
#### (1) 做题顺序
数据结构与算法显然分“结构”与“算法”两个部分，它们结合紧密的同时，又有依赖关系，一个算法往往是针对某种结构设计的，结构的选择影响了算法的选择。因此采取了**先刷结构专题后刷算法专题**的策略。

> 结构 -> 组别一 -> 组别二 -> 组别三 -> 组别四 -> 组别五 -> 组别六

#### (2) 做题策略
1. 没有什么基础知识的情况下可以**每个专题都先只做 1-2 道简单或中等题了解主要思想和内容**，若有一定基础可自行决定跳过部分专题。该阶段各专题的推荐入门题目见[清单](List.md)。
    > 目的是了解各数据结构的基本实现和各算法的概念和原理，大致了解数据结构与算法的知识体系。

2. 每个专题都了解了后可按上面的顺序**从头刷每个专题，每个专题一般不要超过5题，尽量不要超过 10 题**。挑题目时可先看下官方解答，**只做体现目标专题基本内容的模板题，避免总是做到与目标专题相关性低或多专题结合的题目**。此阶段**不用太排斥直接看答案**，同时也**可不追求一道题目的全部官方解答都实现，只实现与目标专题相关的解答**。推荐题目仍见[清单](List.md)。
    > 目的是熟练掌握各数据结构常用的实现和操作的基本模板、各算法的基本模板或模式。

3. 完成上面两个阶段，每个专题都有一定刷题量后，可以混合使用下面的方法：
   - 深入个别专题学习
   - 专题混合练习，了解不同数据结构和算法的使用场合
   - 参加**leetcode周赛**，做限时训练
    > 目的是提升编码熟练度、锻炼算法思维、深入了解使用场景。

#### (3) leetcode测评结果
leetcode 判题系统给的执行时间和消耗内存都只有参考意义，不必强求击败 100%，只要确保代码实现了目标算法即可。

---

### 三、学习资源
#### (1) 参考书籍
- 入门：《大话数据结构》
- 进阶：《算法导论》
- 拓展：《算法竞赛入门经典》(刘汝佳，紫书)

#### (2) 开源社区
- [hello-algo](https://github.com/krahets/hello-algo)
- [fucking-algorithm](https://github.com/labuladong/fucking-algorithm)
- [OI Wiki​](https://github.com/OI-wiki/OI-wiki)
  - 网址: oi-wiki.org
  - [状态页](https://status.oi-wiki.org): 用于监控 OI Wiki 站点的在线情况。如果遇到了无法访问的问题，可以打开状态页，寻找可以连接的镜像站

#### (3) 数学社区
- [Mathematics Stack Exchange](https://math.stackexchange.com)
- [MathOverflow](https://mathoverflow.net)

#### (4) 题库
- [leetcode](https://leetcode.cn/problemset/)
- [洛谷](https://www.luogu.com.cn/)
