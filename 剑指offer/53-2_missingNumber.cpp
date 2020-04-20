// @File   : 53-2_missingNumber.cpp
// @Source : https://leetcode-cn.com/problems/que-shi-de-shu-zi-lcof/
// @Title  : 面试题53 - II. 0～n-1中缺失的数字
// @Auther : sun_ds
// @Date   : 2020/3/30

/**  题目描述：
    一个长度为n-1的递增排序数组中的所有数字都是唯一的，并且每个数字都在范围0～n-1之内。在范围0～n-1内的n个数字中有且只有一个数字不在该数组中，请找出这个数字。

     

    示例 1:

    输入: [0,1,3]
    输出: 2
    示例 2:

    输入: [0,1,2,3,4,5,6,7,9]
    输出: 8
     

    限制：

    1 <= 数组长度 <= 10000

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/que-shi-de-shu-zi-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 二分法
 * nums[i] == i 结果在右边
 * nums[i] != i 结果在左边
 *
 * 特殊情况若数组为0,1,2,3,4,5则应该返回6。
 * 使用l<=r 这样l才会越界返回6
 * 若使用l<r 则只是返回最后一个
 *
 */


class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int l = 0, r = nums.size()-1;
        while(l<=r){
            int mid = l + ((r - l)>>1);
            if(nums[mid]==mid){
                l = mid + 1;
            }else{
                r = mid - 1;
            }
        }
        return l;
    }
};


