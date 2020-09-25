// @File   : 632_smallestRange.cpp
// @Source : https://leetcode-cn.com/problems/smallest-range-covering-elements-from-k-lists/
// @Title  : 632. 最小区间
// @Auther : sun_ds
// @Date   : 2020/8/2

/**  题目描述：
    你有 k 个升序排列的整数数组。找到一个最小区间，使得 k 个列表中的每个列表至少有一个数包含在其中。

    我们定义如果 b-a < d-c 或者在 b-a == d-c 时 a < c，则区间 [a,b] 比 [c,d] 小。

    示例 1:

    输入:[[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
    输出: [20,24]
    解释:
    列表 1：[4, 10, 15, 24, 26]，24 在区间 [20,24] 中。
    列表 2：[0, 9, 12, 20]，20 在区间 [20,24] 中。
    列表 3：[5, 18, 22, 30]，22 在区间 [20,24] 中。
    注意:

    给定的列表可能包含重复元素，所以在这里升序表示 >= 。
    1 <= k <= 3500
    -105 <= 元素的值 <= 105
    对于使用Java的用户，请注意传入类型已修改为List<List<Integer>>。重置代码模板后可以看到这项改动。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/smallest-range-covering-elements-from-k-lists
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 1. 堆
 *  给定 k 个列表，需要找到最小区间，使得每个列表都至少有一个数在该区间中。
 *  该问题可以转化为，从 k 个列表中各取一个数，使得这 k 个数中的最大值与最小值的差最小。
 *
 *  使用 k 大小的小顶堆保存 k 个列表中的最小值。 并使用变量 max_val 保存当前堆中的最大值。
 *
 *  每次从堆中取出最小值，与堆中的最大值组成一个区间。 取出最小值之后放入该列表的下一个值。
 *
 *  当其中一个列表到达末尾，遍历即可结束。剩下的不可能全包括 k 个列表的值。
 *
 *  保存遍历过程中的最小区间即为结果。
 *
 *  时间复杂度 O(N*K*LOG(K)) N为列表平均长度，K 为列表的个数
 *  空间复杂度 O(K)
 *
 *
 * 2. 哈希表 + 滑动窗口
 *
 * 核心在于转换成 B 序列。
 *
 * 可以借鉴「76. 最小覆盖子串」的做法：这里序列 {0,1,⋯,k−1} 就是上面描述的 A 序列，即 k 个列表，我们需要在一个 B 序列当中找到一个区间，可以覆盖 A 序列。
 * 用一个哈希映射来表示 B 序列 B[i] 表示 i 在哪些列表当中出现过，这里哈希映射的键是一个整数，表示列表中的某个数值，哈希映射的值是一个数组，这个数组里的元素代表当前的键出现在哪些列表里。
 * 如果列表集合为：
 *  0: [-1, 2, 3]
 *  1: [1]
 *  2: [1, 2]
 *  3: [1, 1, 3]
 * 那么可以得到这样一个哈希映射
 *  -1: [0]
 *  1: [1, 2, 3, 3]
 *  2: [0, 2]
 *  3: [0, 3]
 * 我们得到的这个哈希映射就是这里的 B 序列。我们要做的就是在 B 序列上使用双指针维护一个滑动窗口，并用一个哈希表维护当前窗口中已经包含了哪些列表中的元素，记录它们的索引。
 * 遍历 B 序列的每一个元素：
 *  指向窗口右边界的指针右移当且仅当每次遍历到新的元素，并将这个新的元素对应的值数组中的每一个数加入到哈希表中。
 *  指向窗口左边界的指针右移当且仅当当前窗口内的元素包含 A 中所有的元素，同时将原来左边界对应的值数组的元素们从哈希表中移除。
 *  答案更新当且仅当当前窗口内的元素包含 A 中所有的元素。
 *
 * 作者：LeetCode-Solution
 * 链接：https://leetcode-cn.com/problems/smallest-range-covering-elements-from-k-lists/solution/zui-xiao-qu-jian-by-leetcode-solution/
 * 来源：力扣（LeetCode）
 * 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 *
 *
 */

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int start = 0, end = INT_MAX;
        int n = nums.size();
        // 记录 k 个列表当前比较到的索引
        vector<int> next(n, 0);

        auto cmp = [&](const int& u, const int& v){
            return nums[u][next[u]] > nums[v][next[v]];
        };

        priority_queue<int, vector<int>, decltype(cmp)> q(cmp);

        int min_val = 0, max_val = INT_MIN;

        // 放入 k 个列表的值
        for (int i=0; i<n; ++i) {
            q.push(i);
            max_val = max(max_val, nums[i][0]);
        }

        while (true) {
            int index = q.top();
            q.pop();
            // 堆顶为当前 k 个值的最小值
            min_val = nums[index][next[index]];

            if (max_val - min_val < end - start) {
                start = min_val;
                end = max_val;
            }
            // 指向当前列表的下一个位置
            ++next[index];
            // 遍历结束
            if (next[index] == nums[index].size()) {
                break;
            }
            // 更新新的最大值
            max_val = max(max_val, nums[index][next[index]]);
            q.push(index);
        }

        return {start, end};
    }
};

// 滑动窗口
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int n = nums.size();
        unordered_map<int, vector<int>> indices;
        int xMin = INT_MAX, xMax = INT_MIN;
        for (int i = 0; i < n; ++i) {
            for (const int& x: nums[i]) {
                indices[x].push_back(i);
                xMin = min(xMin, x);
                xMax = max(xMax, x);
            }
        }

        vector<int> freq(n);
        int inside = 0;
        int left = xMin, right = xMin - 1;
        int bestLeft = xMin, bestRight = xMax;

        while (right < xMax) {
            ++right;
            if (indices.count(right)) {
                for (const int& x: indices[right]) {
                    ++freq[x];
                    if (freq[x] == 1) {
                        ++inside;
                    }
                }
                while (inside == n) {
                    if (right - left < bestRight - bestLeft) {
                        bestLeft = left;
                        bestRight = right;
                    }
                    if (indices.count(left)) {
                        for (const int& x: indices[left]) {
                            --freq[x];
                            if (freq[x] == 0) {
                                --inside;
                            }
                        }
                    }
                    ++left;
                }
            }
        }

        return {bestLeft, bestRight};
    }
};
