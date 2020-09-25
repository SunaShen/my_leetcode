// @File   : 491_findSubsequences.cpp
// @Source : https://leetcode-cn.com/problems/increasing-subsequences/
// @Title  : 491. 递增子序列
// @Auther : sun_ds
// @Date   : 2020/8/25

/**  题目描述：
    给定一个整型数组, 你的任务是找到所有该数组的递增子序列，递增子序列的长度至少是2。

    示例:

    输入: [4, 6, 7, 7]
    输出: [[4, 6], [4, 7], [4, 6, 7], [4, 6, 7, 7], [6, 7], [6, 7, 7], [7,7], [4,7,7]]
    说明:

    给定数组的长度不会超过15。
    数组中的整数范围是 [-100,100]。
    给定数组中可能包含重复数字，相等的数字应该被视为递增的一种情况。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/increasing-subsequences
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. 二进制枚举 + hash 去重
 *  nums 中每个数字选或不选，对应二进制的每个值。
 *  使用二进制枚举，获得所有的子序列。
 *  使用 Rabin-Karp 编码对子序列去重。
 *  判断子序列是否升序。
 *
 * 2. dfs
 *  递归，每个位置选或不选。选中后在判断合法性。
 *
 *  // 如果选择当前元素
 *  temp.push_back(nums[cur]);
 *  dfs(cur + 1, nums);
 *  temp.pop_back();
 *  // 如果不选择当前元素
 *  dfs(cur + 1, nums);
 *
 *  做剪枝。
 *  选择当前元素情况下，当前元素必须不小于前面选中的元素 last。(保证子序列递增)
 *  不选择当前元素的情况下：
 *   考虑相邻元素相同。那么共有四种情况，11，01，10，00. 0 和 1 代表选或不选。
 *   由于元素相邻，所以 01 和 10 在递归过程中，结果一模一样。因此，提前去重。
 *   只保留 01 模式，不要 10 模式。即，当前面选过后，后面无需递归，因为结果在其他分支递归了。
 *
 *
 */

class Solution {
public:
    vector<int> temp;
    vector<vector<int>> ans;
    unordered_set<int> s;
    int n;

    // 获取序列
    void findSubsequences(int mask, vector<int>& nums) {
        temp.clear();
        for (int i = 0; i < n; ++i) {
            if (mask & 1) {
                temp.push_back(nums[i]);
            }
            mask >>= 1;
        }
    }

    // 判断升序
    bool check() {
        for (int i = 1; i < temp.size(); ++i) {
            if (temp[i] < temp[i - 1]) {
                return false;
            }
        }
        return temp.size() >= 2;
    }

    // 获取子串哈希值(去重)
    int getHash(int base, int mod) {
        int hashValue = 0;
        for (const auto &x: temp) {
            // +101使得所有的值都为正数  x = [-100,100]
            hashValue = 1LL * hashValue * base % mod + (x + 101);
            hashValue %= mod;
        }
        return hashValue;
    }

    vector<vector<int>> findSubsequences(vector<int>& nums) {
        n = nums.size();
        // 每个数字选或不选，对应二进制的每个值。
        // 二进制枚举
        for (int i = 0; i < (1 << n); ++i) {
            findSubsequences(i, nums);
            int hashValue = getHash(263, int(1E9) + 7);
            if (check() && s.find(hashValue) == s.end()) {
                ans.push_back(temp);
                s.insert(hashValue);
            }
        }
        return ans;
    }
};

class Solution {
public:
    vector<int> temp;
    vector<vector<int>> ans;

    void dfs(int cur, int last, vector<int>& nums) {
        if (cur == nums.size()) {
            if (temp.size() >= 2) {
                ans.push_back(temp);
            }
            return;
        }
        // 选当前值
        {
            // 保证 temp 递增，仅选不小于 last 的才有意义
            if (nums[cur] >= last) {
                temp.push_back(nums[cur]);
                dfs(cur + 1, nums[cur], nums);
                temp.pop_back();
            }
        }

        // 不选当前值
        {
            // nums[cur] == last时 ， 选择的情况有 11，10，01，00
            // 10，01 的情况结果是相同的。
            // 因此，舍弃 10 的情况。即 当前面选过后，后面无需递归，在其他分支递归了。
            if (nums[cur] != last) {
                dfs(cur + 1, last, nums);
            }
        }
    }

    vector<vector<int>> findSubsequences(vector<int>& nums) {
        dfs(0, INT_MIN, nums);
        return ans;
    }
};

