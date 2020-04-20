// @File   : 162_findPeakElement.cpp
// @Source : https://leetcode-cn.com/problems/find-peak-element/
// @Title  : 162. 寻找峰值
// @Auther : sun_ds
// @Date   : 2020/3/20

/**  题目描述：
    峰值元素是指其值大于左右相邻值的元素。

    给定一个输入数组 nums，其中 nums[i] ≠ nums[i+1]，找到峰值元素并返回其索引。

    数组可能包含多个峰值，在这种情况下，返回任何一个峰值所在位置即可。

    你可以假设 nums[-1] = nums[n] = -∞。

    示例 1:

    输入: nums = [1,2,3,1]
    输出: 2
    解释: 3 是峰值元素，你的函数应该返回其索引 2。
    示例 2:

    输入: nums = [1,2,1,3,5,6,4]
    输出: 1 或 5
    解释: 你的函数可以返回索引 1，其峰值元素为 2；
         或者返回索引 5， 其峰值元素为 6。
    说明:

    你的解法应该是 O(logN) 时间复杂度的。
*/

/**
 *
 * 1.遍历
 *
 * 2.二分法
 *  使用mid和mid+1比较。
 *  如果nums[mid] > nums[mid+1] 峰值在左侧
 *  如果nums[mid] < nums[mid+1] 峰值在右侧
 *
 *
 *
 */


class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        for(int i=0;i<nums.size()-1;i++){
            if(nums[i]>nums[i+1]){
                return i;
            }
        }
        return nums.size()-1;
    }
};
//二分法
class Solution {
public:
    int func(vector<int>& nums,int l,int r){
        if(l==r) return l;
        int mid = (l + r) / 2;
        if(nums[mid] > nums[mid+1]) return func(nums,l,mid);
        else return func(nums,mid+1,r);
    }
    int findPeakElement(vector<int>& nums) {
        return func(nums,0,nums.size()-1);
    }
};
