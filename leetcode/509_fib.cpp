// @File   : 509_fib.cpp
// @Source : https://leetcode-cn.com/problems/fibonacci-number/
// @Title  : 斐波那契数
// @Auther : sun_ds
// @Date   : 2020/2/18

/**  题目描述：
    斐波那契数，通常用 F(n) 表示，形成的序列称为斐波那契数列。该数列由 0 和 1 开始，后面的每一项数字都是前面两项数字的和。也就是：

    F(0) = 0,   F(1) = 1
    F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
    给定 N，计算 F(N)。

     

    示例 1：

    输入：2
    输出：1
    解释：F(2) = F(1) + F(0) = 1 + 0 = 1.
    示例 2：

    输入：3
    输出：2
    解释：F(3) = F(2) + F(1) = 1 + 1 = 2.
    示例 3：

    输入：4
    输出：3
    解释：F(4) = F(3) + F(2) = 2 + 1 = 3.
     

    提示：

    0 ≤ N ≤ 30

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/fibonacci-number
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 * 斐波那契数数
 * F(0) = 0,   F(1) = 1
 * F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
 *
 *
 * 1.递归
 * 时间复杂度：O(2^N)这是计算斐波那契数最慢的方法。因为它需要指数的时间。
 * 空间复杂度：O(N),在堆栈中我们需要与 N 成正比的空间大小。该堆栈跟踪 fib(N) 的函数调用，随着堆栈的不断增长如果没有足够的内存则会导致 StackOverflowError。
 *
 * 2.自底向上进行迭代
 * 若 N <= 1，则返回 N。
 * 若 N == 2，则返回 fib(2-1) + fib(2-2) = 1。
 * 使用迭代的方法，我们至少需要三个变量存储 fib(N), fib(N-1) 和 fib(N-2)。
 * 预置初始值：
 * ans = 0。
 * cur = 1，代表 fib(N-1)。
 * pre = 1，代表 fib(N-2)
 * 我们从 2 计算到 N；0，1，2对应的斐波那契数是预先计算。
 * 设置 ans = fib(N-1) + fib(N-2)，因为 ans 代表的是当前计算的斐波那契数。
 * 设置 pre = cur。
 * 设置 cur = ans。
 * 当我们到达 N+1，将退出循环并返回 current。
 *
 * 时间复杂度O(N)
 * 空间复杂度O(1)
 *
 * 3.矩阵求幂
 *   | f(n)   |  = | 1  1 || f(n-1) | = | 1  1 | ^ n-1 | f(1) |
 *   | f(n-1) |    | 1  0 || f(n-2) |   | 1  0 |       | f(0) |
 *
 *   时间复杂度O(logN)
 *   空间复杂度O(logN)
 *
 * 4.公式法
 * Binet公式： a_n = 1/sqrt(5)[((1+sqrt(5)/2)^n - (1-sqrt(5)/2)^n)]
 * 黄金分割比: phy = (1+sqrt(5)/2
 * 时间复杂度O(1)
 * 空间复杂度O(1)
 *
 *
 */


//递归
class Solution {
public:
    int fib(int N) {
        if (N <= 1) {
            return N;
        }
        return fib(N-1) + fib(N-2);
    }
};
//自底向上进行迭代
class Solution {
public:
    int fib(int N) {
        int pre = 0, cur = 1, ans = 0;
        for(int i=2;i<=N;i++){
            ans = pre + cur;
            pre = cur;
            cur = ans;
        }
        return N==0 ? pre : cur;
    }
};