// @File   : 268_missingNumber.cpp
// @Source : https://leetcode-cn.com/problems/missing-number/
// @Title  : 268. 缺失数字
// @Auther : sun_ds
// @Date   : 2020/5/7

/**  题目描述：
    给定一个包含 0, 1, 2, ..., n 中 n 个数的序列，找出 0 .. n 中没有出现在序列中的那个数。

    示例 1:

    输入: [3,0,1]
    输出: 2
    示例 2:

    输入: [9,6,4,2,3,5,7,0,1]
    输出: 8
    说明:
    你的算法应具有线性时间复杂度。你能否仅使用额外常数空间来实现?

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/missing-number
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.数学
 * 获得总的数字个数，对连续数字，求理想不缺失的和。
 * 使用这个理想不缺失的和 减去 当前数组的和，得到的是缺失的数字的值。
 *
 * 时间复杂度O(N)
 * 空间复杂度O(1)
 *
 * 2.排序判断缺失位
 *
 * 时间复杂度O(NlogN)
 *
 * 3.map
 * 将数组中数字存入map中。
 * 遍历i = 0:n; 如果当前i不在map中则return i;
 * 时间复杂度O(N)
 * 空间复杂度O(N)
 *
 * 4.利用异或
 *  遍历nums，其中i为索引
 *  使用i和nums[i]异或的结果。
 *  由于 相同数字异或等于0.且异或满足结合律。索引中i是0-n，nums中少了数字，索引异或最终结果即为缺失数字。
 *
 *  时间复杂度O(N)
 *  空间复杂度O(1)
 *
 *
 *
 *
 */

//数学
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int sum = n * (n + 1) / 2;
        for(auto i:nums) sum -= i;
        return sum;
    }
};

//异或
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int res=0;
        for(int i=0;i<n;i++){
            res ^= i^nums[i];
        }
        res ^= n;
        return res;
    }
};
