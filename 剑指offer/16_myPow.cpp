// @File   : 16_myPow.cpp
// @Source : https://leetcode-cn.com/problems/shu-zhi-de-zheng-shu-ci-fang-lcof/
// @Title  : 面试题16. 数值的整数次方
// @Auther : sun_ds
// @Date   : 2020/3/8

/**  题目描述：
    实现函数double Power(double base, int exponent)，求base的exponent次方。不得使用库函数，同时不需要考虑大数问题。

     

    示例 1:

    输入: 2.00000, 10
    输出: 1024.00000
    示例 2:

    输入: 2.10000, 3
    输出: 9.26100
    示例 3:

    输入: 2.00000, -2
    输出: 0.25000
    解释: 2-2 = 1/22 = 1/4 = 0.25
     

    说明:

    -100.0 < x < 100.0
    n 是 32 位有符号整数，其数值范围是 [−231, 231 − 1] 。
    注意：本题与主站 50 题相同：https://leetcode-cn.com/problems/powx-n/

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/shu-zhi-de-zheng-shu-ci-fang-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.快速幂
 * x^n = x^n1*x^n2 = x^(n1+n2),其中n1+n2=n
 * 将n展开为2进制数，如该第i位上为1，最终结果上乘x^(2^i)
 * 而x^(2^i)可以由[x^(2^(i-1))]^2推得。
 * 因此可以使用循环
 * for (long i = N; i>0 ; i /= 2) {cur = cur * cur}
 * 获得所有的x^(2^i),在判断该位是否为1决定是否乘到最终结果上
 * 最终得到结果。
 *
 *
 */

class Solution {
public:
    double myPow(double x, int n) {
        long N = n;
        // n = {-2^31,2^31-1}。 若n = -2^31 直接 n=-n会越界
        if(n<0){N = -N; x = 1/x;}
        double res = 1.0, cur = x;
        for(long i=N;i>0;i/=2){
            if(i%2==1)  res = res*cur;
            cur = cur * cur;
        }
        return res;
    }
};