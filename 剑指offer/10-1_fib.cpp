// @File   : 10-1_fib.cpp
// @Source : https://leetcode-cn.com/problems/fei-bo-na-qi-shu-lie-lcof/
// @Title  : 面试题10- I. 斐波那契数列
// @Auther : sun_ds
// @Date   : 2020/2/19

/**  题目描述：
    写一个函数，输入 n ，求斐波那契（Fibonacci）数列的第 n 项。斐波那契数列的定义如下：

    F(0) = 0,   F(1) = 1
    F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
    斐波那契数列由 0 和 1 开始，之后的斐波那契数就是由之前的两数相加而得出。

    答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

     

    示例 1：

    输入：n = 2
    输出：1
    示例 2：

    输入：n = 5
    输出：5
     

    提示：

    0 <= n <= 100
    注意：本题与主站 509 题相同：https://leetcode-cn.com/problems/fibonacci-number/



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/fei-bo-na-qi-shu-lie-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 斐波那契数
 * 1.递归
 * 2.dp
 * 3.矩阵法
 * 4.公式法 黄金分割
 *
 */


//dp
class Solution {
public:
    int fib(int n) {
        if(n == 0) return 0;
        if(n == 1) return 1;
        int pre1 = 1, pre2 = 0;
        long curr;
        for(int i=2;i<=n;i++){
            curr = (pre1 + pre2) % 1000000007;
            pre2 = pre1;
            pre1 = curr;
        }
        return (int)curr;
    }
};


