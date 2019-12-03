// @File   : 53_maxSubArray.cpp
// @Source : https://leetcode-cn.com/problems/maximum-subarray/
// @Title  : 最大子序和
// @Auther : sun_ds
// @Date   : 2019/9/29

/*  题目描述：
    给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

    示例:

    输入: [-2,1,-3,4,-1,2,1,-5,4],
    输出: 6
    解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
    进阶:

    如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的分治法求解。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/maximum-subarray
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
 * 最大子序和
 *
 * 动态规划
 * 动态规划的是首先对数组进行遍历，当前最大连续子序列和为 temp，结果为 res
 * 如果 temp > 0，则说明 temp 对结果有增益效果，则 temp 保留并加上当前遍历数字
 * 如果 temp <= 0，则说明 temp 对结果无增益效果，需要舍弃，则 temp 直接更新为当前遍历数字
 * 每次比较 temp 和 res的大小，将最大值置为res，遍历结束返回结果
 * 时间复杂度：O(n)
 *
 *
 * 注意：
 * for循环中使用 for(auto i:nums)结构，auto会浪费时间，建议int
 *
 *
 * 分治法求解？？？？？？
 *
 */


#include <iostream>
#include <vector>

using namespace std;

//class Solution {
//public:
//    int maxSubArray(vector<int>& nums) {
//        int temp = 0,res = INT_MIN;
//        for(auto i:nums){
//            if(temp < 0){
//                temp = i;
//            } else{
//                temp += i;
//            }
//            if(temp > res)
//                res = temp;
//        }
//        return res;
//    }
//};

//使用auto  8ms
//使用int 4ms
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int temp = 0,res = INT_MIN;
        for(int i:nums){
            temp = max(i,temp+i);
            res = max(temp,res);
        }
        return res;
    }
};



int main()
{
    vector<int> s={-2,1,-3,4,-1,2,1,-5,4};

    Solution su;
    auto res = su.maxSubArray(s);

    cout << res << endl;

    cout << "finish" << endl;
    return 0;
}