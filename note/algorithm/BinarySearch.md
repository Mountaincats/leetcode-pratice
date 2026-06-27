## 二分查找
[TOC]

### 一、理论
**1. 返回插入位置**
有**三种**返回值：**任意满足位置**、 **$upper\_bound$** 和 **$lower\_bound$**，假设数组是：

```
[1, 2, 2, 2, 3]
```
- **任意满足位置**：**任意一个满足要求的插入位置**，下面的结果由**模板(1)** 的算法给出

	| target | 结果 |
	|------|------|
	| 0 | index = 0 |
	| 1 | index = 0 |
	| 2 | index = 2 |
	| 3 | index = 4 |
	| 4 | index = 5 |

- **$lower\_bound$**：**第一个 $\ge target$ 的元素位置**

	| target | 结果 |
	|------|------|
	| 0 | index = 0 |
	| 1 | index = 0 |
	| 2 | index = 1 |
	| 3 | index = 4 |
	| 4 | index = 5 |

- **$upper\_bound$**：**第一个 $\gt target$ 的元素位置**

	| target | 结果 |
	|------|------|
	| 0 | index = 0 |
	| 1 | index = 1 |
	| 2 | index = 4 |
	| 3 | index = 5 |
	| 4 | index = 5 |

**2. 某个值在有序数组中出现的区间(equal_range)**
`equal_range`可以通过**两次二分查找**求出，一次找 **$lower\_bound$**， 一次找 **$upper\_bound$**，最后的区间为 **$[lower\_bound, \; upper\_bound)$**

---

### 二、模板
#### (1) 仅查找 target（不推荐用）
在循环中提前返回插入位置：
```c
int searchInsert(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (nums[mid] < target) left = mid + 1;
        else if (nums[mid] > target) right = mid - 1;
        else return mid;
    }

    return left;
}
```
- 提前返回虽然可能会少几次循环，但意义不大。相反，`if (...) return mid;`是一个不可预测的分支，CPU 分支预测失败会导致流水线清空，在现代 CPU 上反而可能更慢
- 仅能返回查找到的 `target` 位置，不一定是 **$upper\_bound$** 或 **$lower\_bound$**，如在[1, 4, 4, 4, 5] 中查找 4， 返回索引 2，是中间的 4 的索引。这在**无重复元素**的插入中能确定插入位置，但在**有重复元素**的插入中不能确定插入位置

#### (2) 返回 $lower\_bound$
> - 没有提前 return ，CPU 更易优化
> - 只改一行，就能在 **$lower\_bound$** 和 **$upper\_bound$** 间互相转化。而且可以同理推广到别的判断条件，见**抽象模板(4) 示例**

- **写法一**中，left 左边的值一直保持小于 **$target$**，right 右边的值一直保持大于等于 **$target$**，而且 left 最终一定等于 right + 1。
循环结束后，在 left 和 right 之间画一条竖线，恰好可以把数组分为两部分：**left 左边的部分和right右边的部分，而且 left 左边的部分全部小于 $target$，并以 right 结尾；right 右边的部分全部大于等于 $target$，并以 left 为首**。所以 **$lower\_bound$** 位置一定在 left 的位置。

    > 总结：写法一代码中的循环结束后，left = right + 1，且left 始终指向“第一个大于等于 target 的位置”

    ```c
    // 写法一
    int searchInsert(int* nums, int numsSize, int target) {
        int left = 0, right = numsSize - 1;
        // left <= right 的作用是确保 mid 可计算
        while(left <= right) {
            int mid = left + (right - left) / 2;
            // lower_bound 用 <
            if (nums[mid] < target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return left;
    }
    ```
- **写法二**中，left 左边的值一直保持小于 **$target$**，right 右边的值（包括right）一直保持大于等于 **$target$**，而且 left 最终一定等于 right。
循环结束后，left 恰好可以把数组分为两部分：**left 左边的部分全部小于 $target$；以 left 为首的右边的部分全部大于等于 $target$**。所以 **$lower\_bound$** 位置一定在 left 的位置。

    > 总结：写法二代码中的循环结束后，left = right，且left 始终指向“第一个大于等于 target 的位置”
    ```c
    // 写法二
    int searchInsert(int* nums, int numsSize, int target) {
        int left = 0, right = numsSize - 1;
        // left < right 的作用是确保 mid 可计算
        while(left < right) {
            int mid = left + (right - left) / 2;
            // lower_bound 用 <
            if (nums[mid] < target) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        return left;
    }
    ```

#### (3) 返回 $upper\_bound$
> 从 **$lower\_bound$** 模板修改可得到 **$upper\_bound$** 模板


- 写法一中，left 左边的值一直保持小于等于 **$target$**，right 右边的值一直保持大于 **$target$**，而且 left 最终一定等于 right + 1。
循环结束后，在 left 和 right 之间画一条竖线，恰好可以把数组分为两部分：**left 左边的部分和right右边的部分，而且 left 左边的部分全部小于等于 $target$，并以 right 结尾；right 右边的部分全部大于 $target$，并以 left 为首**。所以 **$upper\_bound$** 位置一定在 left 的位置。

    > 总结：写法一代码中的循环结束后，left = right + 1，且 left 始终指向“第一个大于 target 的位置”

    ```c
    // 写法一
    int searchInsert(int* nums, int numsSize, int target) {
        int left = 0, right = numsSize - 1;
        // left <= right 的作用是确保 mid 可计算
        while(left <= right){
            int mid = left + (right - left) / 2;
            // upper_bound 用 <=
            if (nums[mid] <= target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        return left;
    }
    ```

- **写法二**中，left 左边的值一直保持小于等于 **$target$**，right 右边的值（包括right）一直保持大于 **$target$**，而且 left 最终一定等于 right。
循环结束后，left 恰好可以把数组分为两部分：**left 左边的部分全部小于等于 $target$；以 left 为首的右边的部分全部大于 $target$**。所以 **$upper\_bound$** 位置一定在 left 的位置。

    > 总结：写法二代码中的循环结束后，left = right，且 left 始终指向“第一个大于 target 的位置”
    ```c
    // 写法二
    int searchInsert(int* nums, int numsSize, int target) {
        int left = 0, right = numsSize - 1;
        // left < right 的作用是确保 mid 可计算
        while(left < right) {
            int mid = left + (right - left) / 2;
            // upper_bound 用 <=
            if (nums[mid] <= target) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        return left;
    }
    ```

#### (4) 抽象模板
**1. 模板说明**
在有序数组中需要找到首个元素 **$x$** 使 **$f(x)$** 大于或大于等于 **$target$**，其中 **$f(x)$ 为 $x$ 值域内的单调递增函数**。分两个情况，模板中的 **$condition$** 取不同内容。

- 首个 **$f(x) \gt target$**：**$conditon$** 为 **$f(mid) \le target$**，循环结束后 **$left$** 指向从左到右第一个使 **$f(x)$** 大于 **$target$** 的 **$x$**
- 首个 **$f(x) \ge target$**：**$conditon$** 为 **$f(mid) \lt target$**，循环结束后 **$left$** 指向从左到右第一个使 **$f(x)$** 大于等于 **$target$** 的 **$x$**

```c
// 写法一
int search(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1;
    // left <= right 的作用是确保 mid 可计算
    while(left <= right){
        int mid = left + (right - left) / 2;
        if (condition) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return left;
}
```
```c
// 写法二
int searchInsert(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1;
    // left < right 的作用是确保 mid 可计算
    while(left < right) {
        int mid = left + (right - left) / 2;
        if (condition) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }
    return left;
}
```
- **模板(2)** 中相当于 **$f(x) = x \ge target$**
- **模板(3)** 中相当于 **$f(x) = x \gt target$**

**2. 抽象模板使用示例**
计算并返回非负整数 x 的 算术平方根，只保留整数部分，小数部分被舍去。这等价于**在有序数组 $[0, x]$ 中查找首个元素 $mid$ 满足 $mid^2 \gt x$，则 $mid - 1$ 即为算术平方根的整数部分**，这类似于求 **$upper\_bound$**，需要大于 **$target$** 的首个元素。
```c
int mySqrt(int x) {
    int l = 0, r = x;
    while (l < r) {
        int mid = (l + r) / 2;
        if ((long long)mid * mid <= x) {
            l = mid + 1;
        }
        else {
            r = mid;
        }
    }
    return l - 1;
}
```
