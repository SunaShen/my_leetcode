// @File   : 15_hammingWeight.cpp
// @Source : https://leetcode-cn.com/problems/er-jin-zhi-zhong-1de-ge-shu-lcof/
// @Title  : 面试题15. 二进制中1的个数
// @Auther : sun_ds
// @Date   : 2020/3/3

/**  题目描述：
    请实现一个函数，输入一个整数，输出该数二进制表示中 1 的个数。例如，把 9 表示成二进制是 1001，有 2 位是 1。因此，如果输入 9，则该函数输出 2。

    示例 1：

    输入：00000000000000000000000000001011
    输出：3
    解释：输入的二进制串 00000000000000000000000000001011 中，共有三位为 '1'。
    示例 2：

    输入：00000000000000000000000010000000
    输出：1
    解释：输入的二进制串 00000000000000000000000010000000 中，共有一位为 '1'。
    示例 3：

    输入：11111111111111111111111111111101
    输出：31
    解释：输入的二进制串 11111111111111111111111111111101 中，共有 31 位为 '1'。
     

    注意：本题与主站 191 题相同：https://leetcode-cn.com/problems/number-of-1-bits/



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/er-jin-zhi-zhong-1de-ge-shu-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.使用 n&1 取最低位，并n>>=1;
 *  统计最低位为1的个数
 *
 *  复杂度O(log(N))
 *
 * 2.使用n&n-1将n中最低位为1的值置零。
 *  统计置零的次数，即为n中包含1的个数。
 *
 *
 *
 *  n&n-1 将n的最低位为1的位置0
 *  n&-n 取出为1的最低位
 *
 *
 *
 *
 */


//复杂度O(log(N))
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        while(n!=0){
            count += n&1;
            n>>=1;
        }
        return count;
    }
};

//复杂度O(M)
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        while(n!=0){
            count++;
            n &= n-1;
        }
        return count;
    }
};