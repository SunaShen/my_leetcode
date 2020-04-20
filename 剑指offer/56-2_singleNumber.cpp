// @File   : 56-2_singleNumber.cpp
// @Source : https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-ii-lcof/
// @Title  : 面试题56 - II. 数组中数字出现的次数 II
// @Auther : sun_ds
// @Date   : 2020/4/4

/**  题目描述：
    在一个数组 nums 中除一个数字只出现一次之外，其他数字都出现了三次。请找出那个只出现一次的数字。

     

    示例 1：

    输入：nums = [3,4,3,3]
    输出：4
    示例 2：

    输入：nums = [9,1,7,9,7,9,7]
    输出：1
     

    限制：

    1 <= nums.length <= 10000
    1 <= nums[i] < 2^31
     

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-ii-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 *
 * 三进制加法。
 *
 * one中的1代表该位置有1或3个1.
 * two中的1代表该位置有2个1.
 * three中的1代表该位置有3个1.
 *
 * three中的1代表出现了三次，消消乐。将two和one对应位置也清零。
 *
 *
 *
 */

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int one=0,two=0,three=0;
        for(auto i:nums){
            two |= one&i;
            one ^= i;
            three = two&one;
            one &= ~three;
            two &= ~three;
        }
        return one;
    }
};
