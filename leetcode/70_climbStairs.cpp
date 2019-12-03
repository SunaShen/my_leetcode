// @File   : 70_climbStairs.cpp
// @Source : https://leetcode-cn.com/problems/climbing-stairs/
// @Title  : 爬楼梯
// @Auther : sun_ds
// @Date   : 2019/9/29

/*  题目描述：
    假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

    每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

    注意：给定 n 是一个正整数。

    示例 1：

    输入： 2
    输出： 2
    解释： 有两种方法可以爬到楼顶。
    1.  1 阶 + 1 阶
    2.  2 阶
            示例 2：

    输入： 3
    输出： 3
    解释： 有三种方法可以爬到楼顶。
    1.  1 阶 + 1 阶 + 1 阶
    2.  1 阶 + 2 阶
    3.  2 阶 + 1 阶

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/climbing-stairs
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
 * 爬楼梯
 *
 * 1.找规律
 * 使用组合数计算。
 * 包含大量阶乘运算，计算复杂度太高，而且阶乘容易溢出。
 *
 * 2.递归
 * 好写，复杂度高，O(2^n)
 * 2.1 带有memo的递归？
 * 存储计算过的值
 *
 *
 * 3.动态规划 nice
 * dp[n] = dp[n-1] + dp[n-2]
 * dp[1]=1
 * dp[2]=2
 *
 * 斐波那契数列？
 * 可以不用数组dp[n]，节约空间复杂度
 *
 * 采用斐波那契数列的操作
 * 矩阵法
 * 公式法
 *
 *
 */







#include <iostream>
#include <vector>

using namespace std;

//n>=22就会出错！！（阶乘溢出？）
//找规律，使用组合数相加。
//其中包含大量阶乘运算，效率低下！！
//class Solution {
//public:
//    long factorial(long number)
//    {	if(number<=1) return 1;
//        else return number*factorial(number-1);
//    }
//
//    int combine(int m, int n){
//        return factorial(n)/(factorial(n-m)*factorial(m));
//    }
//
//    int climbStairs(int n) {
//        if(n==0 || n==1)
//            return n;
//        int res=1;
//        for(int i=n-1;i>=n/2;i--){
//            res += combine(n-i,i);
//        }
//        return res;
//    }
//};



// 暴力递归
// 好写
// 复杂度高 O(2^n)
//class Solution {
//public:
//    int climbStairs(int n) {
//        if(n<=1) return 1;
//        else
//            return climbStairs(n - 1) + climbStairs(n - 2);
//    }
//};




class Solution {
public:
    int climbStairs(int n) {
        if(n<=1)
            return 1;
        int dp[n+1];
        dp[0] = dp[1] = 1;
        for(int i=2;i<=n;i++){
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n];
    }
};


int main()
{
    int n=10;

    Solution su;
    auto res = su.climbStairs(n);

    cout << res << endl;

    cout << "finish" << endl;
    return 0;
}