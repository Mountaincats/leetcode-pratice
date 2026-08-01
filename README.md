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

#### (2) 算法
- **组别一**
  - 二分查找(Binary Search)
  - 排序
    - 排序(Sort)
    - 堆排序(Heap Sort)
    - 归并排序(Merge Sort)
    - 计数排序(Counting Sort)
    - 基数排序(Radix Sort)
    - 桶排序(Bucket Sort)
    - 拓扑排序(Topological Sort)
- **组别二**
  - 双指针(Two Pointers)
  - 滑动窗口(Sliding Window)
  - 前缀和(Prefix Sum)
- **组别三**
  - 回溯(Backtracking)
  - 递归(Recursion)
  - 分治(Divide And Conquer)
- **组别四**
  - 贪心(Greedy)
  - 动态规划(Dynamic Programming)
- **组别五**
	- 位运算(Bitwise Operation)
	- 位掩码(Bitmask)
- **组别六**
  - 广度优先搜索(Breadth First Search, BFS)
  - 深度优先搜索(Depth First Search, DFS)

#### (3) 难点专题
- 字符串
- 图
- 回溯
- 递归
- 分治
- 贪心
- 动态规划

---

### 二、leetcode 使用
#### (1) 做题顺序
数据结构与算法显然分“结构”与“算法”两个部分，它们结合紧密的同时，又有依赖关系，一个算法往往是针对某种结构设计的，结构的选择影响了算法的选择，因此采取了**先刷结构专题后刷算法专题**的策略。但其中图比较复杂且与算法关联较大，所以可以放最后做。

> 结构 -> 组别一 -> 组别二 -> 组别三 -> 组别四 -> 组别五 -> 组别六 -> 图

#### (2) 做题策略
1. 没有什么基础知识的情况下可以**每个专题都先只做 1-2 道简单或中等题了解主要思想和内容**，若有一定基础可自行决定跳过部分专题。该阶段各专题的推荐入门题目见[清单](List.md)。
    > 目的是了解各数据结构的基本实现和各算法的概念和原理，大致了解数据结构与算法的知识体系。

2. 每个专题都了解了后可按上面的顺序**从头刷每个专题，每个专题一般不要超过 10 题，尽量不要超过 15 题**。挑题目时可先看下官方解答，**只做体现目标专题基本内容的模板题，避免总是做到与目标专题相关性低或多专题结合的题目**。此阶段**不用太排斥直接看答案**，同时也**可不追求实现一道题目的全部官方解答，可以只实现与目标专题相关的解答**。推荐题目仍见[清单](List.md)。
    > 目的是掌握各数据结构常用的实现和操作的基本模板、各算法的基本模板或模式。

3. 完成上面两个阶段，掌握每个专题后，可以进行**专题、混合、限时训练**来进一步提升。一个具体的参考学习方案是平常可以挑选感兴趣或不擅长的专题进行针对学习，同时参加 **leetcode 周赛**，等 LC 周赛能稳定做出前 3 题时可额外参加 **Codeforces 比赛**。
    > 目的是提升编码熟练度、锻炼算法思维、了解不同数据结构和算法的使用场合。

#### (3) leetcode 测评结果
leetcode 判题系统给的执行时间和消耗内存都只有参考意义，不必强求击败 100%，只要确保代码实现了目标算法即可。

---

### 三、学习资源
#### (1) 参考资料
- 入门：
  - 《大话数据结构》(程杰)
  - [《hello-algo》](https://github.com/krahets/hello-algo)
  - [《fucking-algorithm》](https://github.com/labuladong/fucking-algorithm)
- 进阶：
  - 《算法竞赛入门经典》(刘汝佳，紫书)
  - [OI Wiki​](https://oi-wiki.org)
    - 编程竞赛知识整合
    - [仓库地址](https://github.com/OI-wiki/OI-wiki)

#### (2) 社区
- 数学社区
  - [Mathematics Stack Exchange](https://math.stackexchange.com)
  - [MathOverflow(MO)](https://mathoverflow.net)
- 算法社区
  - [Stack Overflow(SO)](https://stackoverflow.co/)
  - [Computer Science Stack Exchange(CS SE)](https://cs.stackexchange.com/)
  - [Theoretical Computer Science Stack Exchange(TCS SE / cstheory)](https://cstheory.stackexchange.com/)

#### (3) 题库
- [leetcode(LC)](https://leetcode.cn/problemset/)
- [Codeforces(CF)](https://codeforces.com/problemset)
- [洛谷](https://www.luogu.com.cn/)

#### (4) 比赛
- **leetcode 周赛**
  - 单、双周赛
  - 一次时长 2 小时，2 道 easy，1 道 medium，1 道 hard
  - 面向面试准备，题目偏向工程面试常见套路
- **Codeforces Round**
  - 全球最主流的个人在线算法竞赛平台
  - 每年举办 300+ 场比赛，几乎每周都有，包含 Div.1、Div.2、Div.3、Div.4、Educational Round、Global Round 等多种类型
  - 一般 2 到 2.5 小时，一次 5-8 道题，按难度升序排列
  - 面向算法竞技，题目偏向数学竞赛风格，强调建模能力和极限优化