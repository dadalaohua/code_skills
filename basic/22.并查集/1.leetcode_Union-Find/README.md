# 按公因数计算最大组件大小

给定一个由不同正整数的组成的非空数组 nums ，考虑下面的图：

有 nums.length 个节点，按从 nums[0] 到 nums[nums.length - 1] 标记；
只有当 nums[i] 和 nums[j] 共用一个大于 1 的公因数时，nums[i] 和 nums[j]之间才有一条边。
返回 图中最大连通组件的大小 。

 

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/largest-component-size-by-common-factor
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



为了得到数组 $\textit{nums}$ 中的每个数和哪些数属于同一个组件，需要得到数组 $\textit{nums}$ 中的最大值 mm，对于每个不超过 $m$ 的正整数 $\textit{num}$ 计算 $\textit{num}$ 和哪些数属于同一个组件。对于范围 $[2, \sqrt{\textit{num}}]$内的每个正整数 $i$，如果 $i$ 是 $\textit{num}$ 的因数，则 $\textit{num}$ 和 $i$、$\dfrac{\textit{num}}{i}$ 都属于同一个组件。

可以使用并查集实现组件的计算。初始时，每个数分别属于不同的组件。如果两个正整数满足其中一个正整数是另一个正整数的因数，则这两个正整数属于同一个组件，将这两个正整数的组件合并。

当所有不超过 $m$ 的正整数都完成合并操作之后。遍历数组 $\textit{nums}$，对于每个数得到其所在的组件并更新该组件的大小，遍历结束之后即可得到最大组件的大小。

作者：LeetCode-Solution
链接：https://leetcode.cn/problems/largest-component-size-by-common-factor/solution/an-gong-yin-shu-ji-suan-zui-da-zu-jian-d-amdx/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。