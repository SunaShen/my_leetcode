// @File   : 42_maxSubArray.cpp
// @Source : https://leetcode-cn.com/problems/lian-xu-zi-shu-zu-de-zui-da-he-lcof/
// @Title  : 面试题42. 连续子数组的最大和
// @Auther : sun_ds
// @Date   : 2020/3/15

/**  题目描述：
    输入一个整型数组，数组里有正数也有负数。数组中的一个或连续多个整数组成一个子数组。求所有子数组的和的最大值。

    要求时间复杂度为O(n)。

     

    示例1:

    输入: nums = [-2,1,-3,4,-1,2,1,-5,4]
    输出: 6
    解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
     

    提示：

    1 <= arr.length <= 10^5
    -100 <= arr[i] <= 100
    注意：本题与主站 53 题相同：https://leetcode-cn.com/problems/maximum-subarray/

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/lian-xu-zi-shu-zu-de-zui-da-he-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.贪心
 * 当叠加的和小于0时，就从下一个数重新开始，
 * 同时更新最大和的值(最大值可能为其中某个值)
 * 当叠加和大于0时，将下一个数值加入和中，
 * 同时更新最大和的值，依此继续。
 *
 *
 *
 *
 */



class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int dp = 0, res = INT_MIN;
        for(int i=0;i<nums.size();i++){
            dp = max(nums[i],dp+nums[i]);
            res = max(res,dp);
        }
        return res;
    }
};


