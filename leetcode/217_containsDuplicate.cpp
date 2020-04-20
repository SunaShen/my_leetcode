// @File   : 217_containsDuplicate.cpp
// @Source : https://leetcode-cn.com/problems/contains-duplicate/
// @Title  : 217. 存在重复元素
// @Auther : sun_ds
// @Date   : 2020/3/19

/**  题目描述：
    给定一个整数数组，判断是否存在重复元素。

    如果任何值在数组中出现至少两次，函数返回 true。如果数组中每个元素都不相同，则返回 false。

    示例 1:

    输入: [1,2,3,1]
    输出: true
    示例 2:

    输入: [1,2,3,4]
    输出: false
    示例 3:

    输入: [1,1,1,3,3,4,3,2,4,2]
    输出: true
*/

/**
 *
 * 适用map统计
 *
 */

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int,int> m;
        for(auto i:nums)
            if(m[i]>0) return true;
            else m[i]++;
        return false;
    }
};