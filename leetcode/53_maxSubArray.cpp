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


/**
 * 最大子序和
 *
 * 1.动态规划
 * 动态规划的是首先对数组进行遍历，当前最大连续子序列和为 temp，结果为 res
 * 如果 temp > 0，则说明 temp 对结果有增益效果，则 temp 保留并加上当前遍历数字
 * 如果 temp <= 0，则说明 temp 对结果无增益效果，需要舍弃，则 temp 直接更新为当前遍历数字
 * 每次比较 temp 和 res的大小，将最大值置为res，遍历结束返回结果
 * 时间复杂度：O(n)
 * 空间复杂度: O(1)
 *
 * 注意：
 * for循环中使用 for(auto i:nums)结构，auto会浪费时间，建议int
 *
 *
 * 2.分治法(线段树)
 * 对于每一个区间[l,r]维护四个值。
 *   1)lSum:以l为左端点的最大子段和
 *   2)rSum:以r为右端点的最大子段和
 *   3)mSum:区间内的最大子段和
 *   4)iSum:整个区间和
 * 二分的划分区间。当区间内只有一个值时，上面四个取值都为该值，返回。
 * 二分递归返回后，需要合并。
 *   左右两部分区间合并[l,mid]和[mid+1,r]
 *   1)合并后区间和 = 左区间和 + 右区间和;
 *   2)合并后以l为左端点的最大子段和 = max(左区间左端点的最大子段和，左区间和+右区间的左端点最大子段和);
 *   3)合并后以r为右端点的最大子段和 = max(右区间右端点的最大子段和，右区间和+左区间的右端点最大子段和);
 *   4)合并后区间内最大字段和 = max(左区间的最大子段和，右区间的最大子段和，左区间的右端点最大子段和+右区间的左端点最大子段和);
 *
 * 时间复杂度:O(sum(2^i-1)) i = [1,log(n)]  故渐进时间复杂度为O(N)
 * 空间复杂度:O(logN) 递归的栈空间
 *
 * 优势：可以求任意区间内的最大子段和。
 *
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



//线段树思想
class Solution {
public:
    struct Status {
        //当前区间[l,r]
        //lSum:以l为左端点的最大子段和
        //rSum:以r为右端点的最大子段和
        //mSum:区间内的最大子段和
        //iSum:整个区间和
        int lSum, rSum, mSum, iSum;
    };

    Status pushUp(Status l, Status r) {
        //左右两部分区间合并[l,mid]和[mid+1,r]
        //合并后区间和 = 左区间和 + 右区间和;
        int iSum = l.iSum + r.iSum;
        //合并后以l为左端点的最大子段和 = max(左区间左端点的最大子段和，左区间和+右区间的左端点最大子段和);
        int lSum = max(l.lSum, l.iSum + r.lSum);
        //合并后以r为右端点的最大子段和 = max(右区间右端点的最大子段和，右区间和+左区间的右端点最大子段和);
        int rSum = max(r.rSum, r.iSum + l.rSum);
        //合并后区间内最大字段和 = max(左区间的最大子段和，右区间的最大子段和，左区间的右端点最大子段和+右区间的左端点最大子段和);
        int mSum = max(max(l.mSum, r.mSum), l.rSum + r.lSum);
        return (Status) {lSum, rSum, mSum, iSum};
    };

    Status get(vector<int> &a, int l, int r) {
        //区间内只有一个元素，四个值都是他本身
        if (l == r) return (Status) {a[l], a[l], a[l], a[l]};
        //分治
        int m = (l + r) >> 1;
        Status lSub = get(a, l, m);
        Status rSub = get(a, m + 1, r);
        //合并
        return pushUp(lSub, rSub);
    }

    int maxSubArray(vector<int>& nums) {
        //返回区间的最大子段和
        return get(nums, 0, nums.size() - 1).mSum;
    }
};



//int main()
//{
//    vector<int> s={-2,1,-3,4,-1,2,1,-5,4};
//
//    Solution su;
//    auto res = su.maxSubArray(s);
//
//    cout << res << endl;
//
//    cout << "finish" << endl;
//    return 0;
//}