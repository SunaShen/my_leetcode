// @File   : 209_minSubArrayLen.cpp
// @Source : https://leetcode-cn.com/problems/minimum-size-subarray-sum/
// @Title  : 长度最小的子数组
// @Auther : sun_ds
// @Date   : 2019/12/11

/**  题目描述：
    给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的连续子数组。如果不存在符合条件的连续子数组，返回 0。

    示例: 

    输入: s = 7, nums = [2,3,1,2,4,3]
    输出: 2
    解释: 子数组 [4,3] 是该条件下的长度最小的连续子数组。
    进阶:

    如果你已经完成了O(n) 时间复杂度的解法, 请尝试 O(n log n) 时间复杂度的解法。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/minimum-size-subarray-sum
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 找出数组中和大于等于给定值s的最短的连续子数组。
 *
 * 1.双指针
 *   使用双指针，左右指针分别指向子数组两端。
 *   开始时，两个指针都在数组的第一个值位置。
 *   若两指针之间子数组的和满足条件，则将当前子数组长度与记录的最小长度比较更新，左指针向右
 *   若两指针之间子数组的和不满足条件，则右指针向右
 */

class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int n = nums.size();
        int l = 0,r = 0;
        int sum = 0,res = INT_MAX;
        //r就是子数组右边界的右边的位置.
        while(r<n||(sum>=s&&r==n)){
            if(sum<s){
                sum += nums[r];
                ++r;
            }else{
                //先更新sum,++r; 此时r就是子数组右边界的右边的位置
                res = min(res,r-l);
                sum-=nums[l];
                ++l;
            }
        }
        return res==INT_MAX?0:res;
    }
};


class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int n = nums.size();
        int l = 0,r = 0;
        int sum = 0,res = INT_MAX;
        while(r<n){
            if(sum + nums[r] <s){
                sum += nums[r];
                ++r;
            }else{
                //后更新sum,++r; 此时r就是子数组右边界
                res = min(res,r-l+1);
                sum-=nums[l];
                ++l;
            }
        }
        return res==INT_MAX?0:res;
    }
};

