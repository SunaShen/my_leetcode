// @File   : 343_integerBreak.cpp
// @Source : https://leetcode-cn.com/problems/integer-break/
// @Title  : 整数拆分
// @Auther : sun_ds
// @Date   : 2019/12/9

/**  题目描述：
    给定一个正整数 n，将其拆分为至少两个正整数的和，并使这些整数的乘积最大化。 返回你可以获得的最大乘积。

    示例 1:

    输入: 2
    输出: 1
    解释: 2 = 1 + 1, 1 × 1 = 1。
    示例 2:

    输入: 10
    输出: 36
    解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36。
    说明: 你可以假设 n 不小于 2 且不大于 58。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/integer-break
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 一个正整数 n，将其拆分为至少两个正整数的和，并使这些整数的乘积最大化
 * 1.dp
 * 子问题分解
 * 当前最大乘积dp[i]拆分成两部分，即dp[i-j]和dp[j].
 * 即dp[i] = dp[i-j]*dp[j]  其中j=[1,i-1] i-j+j保证正整数之和为i。并且两个部分都是最大的相乘也比较大
 * 无法确定j取多少时dp[i]最大，所以遍历所有j。
 * 遍历i=[1,n]
 * 最终得到dp[n]即为所求结果
 *
 * 实际转移方程 dp[i] = max(max(i-j, dp[i-j])*max(j,dp[j])); j=[1,i-1]
 * 应题目要求，dp[i]默认代表至少拆成两项。而当i-j和j作为i拆出的一部分时，可以不用满足至少拆分成两项的规则。
 * 因此使用max(i-j,dp[i-j])和max(j,dp[j]),防止漏掉不拆分的情况。
 *
 * 2.贪心
 * https://leetcode-cn.com/problems/integer-break/solution/343-zheng-shu-chai-fen-tan-xin-by-jyd/
 * 除了整数2和3其余整数均需要拆分才能够获得更大的乘积，因此最后拆分的终止即全由2和3组成
 * 除此之外，同一个数，全拆成3比全拆成2的乘积要大
 * 因此，尽量将该值全部拆成由3组成
 * 特殊情况。当n%3==1时，结果不是3^a*1.而是向前借个3,构成3^(a-1)*2*2.原因是2*2=4比3*1=3要大.
 *
 *
 * 算法流程:
 *      1.当n<=3时，按照贪心规则应直接保留原数字，但由于题目要求必须拆分，因此必须拆出一个1，即直接返回n-1
 *      2.求n除以3的整数部分a和余数部分b
 *      3.当b==0时，直接返回3^a
 *      4.当b==1时，要将一个1+3转换成2+2，此时返回3^(a-1)*2
 *      5.当b==2时，返回3^a*b
 *
 */

//dp
class Solution {
public:
    int integerBreak(int n) {
        int dp[n+1];
        memset(dp,0,sizeof(dp));
        dp[1] = 1;
        for(int i=2;i<=n;++i){
            //从中间向两边考虑。两边的都可继续拆或不拆。
            //j从1~i/2 即可 对称的
            for(int j=1;j<=i/2;++j){
                dp[i] = max(dp[i], max(i-j, dp[i-j])*max(j,dp[j]));
            }
        }
        return dp[n];
    }
};

class Solution {
public:
    int integerBreak(int n) {
        int dp[n+1];
        memset(dp,0,sizeof(dp));
        dp[1] = 1;
        for(int i=2;i<=n;++i){
            //从前往后考虑，每次固定第一个值。
            //固定，i拆分出j，至于i-j可拆可不拆
            //j<=i/2 结果也对，由下面贪心可知，总是拆成多个3，所以后面也是浪费的。但直接j<=i/2没有意义。
            for(int j=1;j<i;++j){
                dp[i] = max(dp[i], j*max(i-j, dp[i-j]));
            }
        }
        return dp[n];
    }
};

//贪心
class Solution {
public:
    int integerBreak(int n) {
        if(n<=3) return n-1;
        int a = n/3, b = n%3;
        if(b==0) return pow(3,a);
        else if(b==1) return pow(3,a-1)*4;
        else return pow(3,a)*2;
    }
};
