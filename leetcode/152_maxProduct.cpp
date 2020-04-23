// @File   : 152_maxProduct.cpp
// @Source : https://leetcode-cn.com/problems/maximum-product-subarray/
// @Title  : 152. 乘积最大子数组
// @Auther : sun_ds
// @Date   : 2020/4/23

/**  题目描述：
    给你一个整数数组 nums ，请你找出数组中乘积最大的连续子数组（该子数组中至少包含一个数字）。

     

    示例 1:

    输入: [2,3,-2,4]
    输出: 6
    解释: 子数组 [2,3] 有最大乘积 6。
    示例 2:

    输入: [-2,0,-1]
    输出: 0
    解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/maximum-product-subarray
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.动态规划？
 * Max和Min保存当前位置前的最大乘积和最小乘积(可能有负数)
 *
 * 遍历更新，res保存过程中乘积的最大值。
 * 当前位置乘积最大值 可能是 当前值*前面最大值 或者 当前值(负数)*前面最小值 或者 自己本身
 * 所以要实时保存最大值和最小值。
 *
 * 1.1 nums[i]为正值
 *  max(Max*nums[i],nums[i])
 *  min(Min*nums[i],nums[i])
 * 1.2 nums[i]为负值
 *  max(Min*nums[i],nums[i])
 *  min(Max*nums[i],nums[i])
 *
 * 合并一起：
 * 当前位置的最大乘积为:
 *  max(Max*nums[i],Min*nums[i],nums[i])
 * 当前位置的最小乘积为:
 *  min(Max*nums[i],Min*nums[i],nums[i])
 *
 *
 */

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int res=nums[0];
        int Max = nums[0],Min = nums[0];
        for(int i=1;i<n;i++){
            int temp = Max;
            Max = max(max(Max*nums[i],Min*nums[i]),nums[i]);
            Min = min(min(temp*nums[i],Min*nums[i]),nums[i]);
            res = max(res,Max);
        }
        return res;
    }
};


