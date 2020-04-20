// @File   : 56-1_singleNumbers.cpp
// @Source : https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof/
// @Title  : 面试题56 - I. 数组中数字出现的次数
// @Auther : sun_ds
// @Date   : 2020/4/4

/**  题目描述：
    一个整型数组 nums 里除两个数字之外，其他数字都出现了两次。请写程序找出这两个只出现一次的数字。要求时间复杂度是O(n)，空间复杂度是O(1)。

     

    示例 1：

    输入：nums = [4,1,4,6]
    输出：[1,6] 或 [6,1]
    示例 2：

    输入：nums = [1,2,10,4,1,4,3,3]
    输出：[2,10] 或 [10,2]
     

    限制：

    2 <= nums <= 10000
     

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 已知 0异或任何数都不变。
 * 任何数异或他本身都是0.
 * 若，数组中只有一个数是一个，其他都是两个。那么之间遍历，异或。得到的最终值即为那个单独的值。
 *
 * 该题目中，有两个单个的数字。
 * 遍历异或之后，得到的temp是单独的两个数a和b的异或结果。
 *
 * 如何从temp区分出a和b呢。
 * 使用temp对所有数进行分组。 利用temp&-temp使得temp中只有最后一个1保留，其他都是0.
 * 每次是得nums中的值与temp&-temp做位与，为0分为一类，为1分为一类。
 * 则，相同的数字肯定是被分到了一类中，而a和b是肯定被分到了不同的类别。
 * 所以，得到的区分出了a和b
 *
 *
 */

class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int temp=0;
        int a=0,b=0;
        for(auto i:nums) temp^=i;
        temp = temp&-temp;
        for(auto i:nums){
            if(temp&i){
                a^=i;
            }else{
                b^=i;
            }
        }
        return {a,b};
    }
};

