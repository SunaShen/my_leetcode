// @File   : 14-2_cuttingRope.cpp
// @Source : https://leetcode-cn.com/problems/jian-sheng-zi-ii-lcof/
// @Title  : 面试题14- II. 剪绳子 II
// @Auther : sun_ds
// @Date   : 2020/3/7

/**  题目描述：
    给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m] 。请问 k[0]*k[1]*...*k[m] 可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。

    答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

     

    示例 1：

    输入: 2
    输出: 1
    解释: 2 = 1 + 1, 1 × 1 = 1
    示例 2:

    输入: 10
    输出: 36
    解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36
     

    提示：

    2 <= n <= 1000
    注意：本题与主站 343 题相同：https://leetcode-cn.com/problems/integer-break/

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/jian-sheng-zi-ii-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 1.贪心+快速幂
 * 求最大值：
 *  除了整数2和3其余整数均需要拆分才能够获得更大的乘积，因此最后拆分的终止即全由2和3组成
 *  除此之外，同一个数，全拆成3比全拆成2的乘积要大
 *  因此，尽量将该值全部拆成由3组成
 *  特殊情况。当n%3==1时，结果不是3^a*1.而是向前借个3,构成3^(a-1)*2*2.原因是2*2=4比3*1=3要大.
 *  算法流程:
 *          1.当n<=3时，按照贪心规则应直接保留原数字，但由于题目要求必须拆分，因此必须拆出一个1，即直接返回n-1
 *          2.求n除以3的整数部分a和余数部分b
 *          3.当b==0时，直接返回3^a
 *          4.当b==1时，要将一个1+3转换成2+2，此时返回3^(a-1)*2
 *          5.当b==2时，返回3^a*b
 * 求幂：
 * 由于数字太大。直接使用pow会溢出。
 * 所以需自己实现幂算法
 * leetcode 50.Pow(x, n)
 * https://leetcode-cn.com/problems/powx-n/
 * 方法：1.递归 2.快速幂
 * 快速幂：
 *  x^n = x^n1*x^n2 = x^(n1+n2),其中n1+n2=n
 *  将n展开为2进制数，如该第i位上为1，最终结果上乘x^(2^i)
 *  而x^(2^i)可以由[x^(2^(i-1))]^2推得。
 *  因此可以使用循环
 *  for (long long i = N; i ; i /= 2) {current_product = current_product * current_product}
 *  获得所有的x^(2^i),在判断该位是否为1决定是否乘到最终结果上
 *  最终得到结果。
 *
 *  在运算中间时刻对1e9+7（1000000007）求余，防止溢出
 *
 *
 *  乘法求余数公式
 *  (x*y)%p = [(x%p)*(y%p)]%p
 *
 *
 *
 *
 *
 */

class Solution {
public:
    int cuttingRope(int n) {
        if(n<=3) return n-1;
        int p = 1000000007;
        long long rem = 1, x = 3;
        //快速幂
        for(int i=n/3-1;i>0;i/=2){
            if(i%2==1) rem = (rem*x)%p;
            //x使用long long   x*x<=1000000007^2<2^63-1
            x = (x * x)%p;
        }
        if(n%3==0) return (rem*3)%p;
        else if(n%3==1) return (rem*4)%p;
        else return (rem*6)%p;
    }
};