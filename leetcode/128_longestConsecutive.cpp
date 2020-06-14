// @File   : 128_longestConsecutive.cpp
// @Source : https://leetcode-cn.com/problems/longest-consecutive-sequence/
// @Title  : 128. 最长连续序列
// @Auther : sun_ds
// @Date   : 2020/6/6

/**  题目描述：
    给定一个未排序的整数数组，找出最长连续序列的长度。

    要求算法的时间复杂度为 O(n)。

    示例:

    输入: [100, 4, 200, 1, 3, 2]
    输出: 4
    解释: 最长连续序列是 [1, 2, 3, 4]。它的长度为 4。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/longest-consecutive-sequence
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 思路：以每个数字为起点向后遍历，满足连续则继续，否则重新开始，得到最大的连续的长度即为结果。
 *
 * 其中有一些重复搜索。
 * 如[100, 4, 200, 1, 3, 2]中，以 1 位起点得到 1,2,3,4。包含了 2 为起点的 2，3，4。
 * 所以每个有用的起点为其前面的数字不存在。
 *
 * 使用 unordered_set 存储各个数字。（自带去重，且查找复杂度 O(1)）
 *
 * 外层循环需要 O(n) 的时间复杂度，只有当一个数是连续序列的第一个数的情况下才会进入内层循环，
 * 然后在内层循环中匹配连续序列中的数，因此数组中的每个数只会进入内层循环一次。
 * 最终得，总时间复杂度为 O(n)
 *
 *
 */

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> s;
        int res = 0;
        for(auto num:nums) s.insert(num);
        for(int i=0;i<nums.size();i++){
            if(s.count(nums[i]-1)) continue;
            int temp = nums[i];
            int len = 1;
            while(s.count(temp+1)){
                len += 1;
                temp += 1;
            }
            res = max(res,len);
        }
        return res;
    }
};


