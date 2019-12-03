// @File   : 50_myPow.cpp
// @Source : https://leetcode-cn.com/problems/powx-n/
// @Title  : Pow(x, n)
// @Auther : sun_ds
// @Date   : 2019/10/28

/*  题目描述：
    实现 pow(x, n) ，即计算 x 的 n 次幂函数。

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
    n 是 32 位有符号整数，其数值范围是 [−2^31, 2^31 − 1] 。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/powx-n
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
 *
 * pow(x,n)
 *
 * x的n次方。首先处理n，n可正可负。32位int
 * 需要将n为负数时转换成正数，但注意INT_MIN直接取负号越界。因此需使用long long N；
 *
 * 1.暴力解
 * 复杂度 O(n)
 * 2.递归
 * 分治法，一直二分，区别奇数和偶数
 * n为偶数:x^n = x^(n/2)*x^(n/2)
 * n为奇数:x^n = x^(n/2)*x^(n/2)*x
 * 算法复杂度 O(log(n))
 * 空间复杂度 O(log(n))
 *
 * 3.循环
 * x^n = x^n1*x^n2 = x^(n1+n2),其中n1+n2=n
 * 将n展开为2进制数，如该第i位上为1，最终结果上乘x^(2^i)
 * 而x^(2^i)可以由[x^(2^(i-1))]^2推得。
 * 因此可以使用循环
 * for (long long i = N; i ; i /= 2) {current_product = current_product * current_product}
 * 获得所有的x^(2^i),在判断该位是否为1决定是否乘到最终结果上
 * 最终得到结果。
 *
 * 算法复杂度 O(log(n))
 * 空间复杂度 O(1)
 *
 *
 *
 */


class Solution {
public:
    double fun(double x, long long n){
        if(n==1)
            return x;
        double ans = 1.0;
        ans = fun(x, n/2);
        ans *= ans;
        if(n%2!=0){
            ans *= x;
        }
        return ans;
    }
    double myPow(double x, int n) {
        if(n==0)
            return 1;
        if(x==0||x==1)
            return x;
        long long N = n;
        if(n<0){
            x = 1/x;
            N = -N;
        }
        return fun(x,N);
    }
};

//快速幂算法(递归）
class Solution {
public:
    double fastPow(double x, long long n) {
        if (n == 0) {
            return 1.0;
        }
        double half = fastPow(x, n / 2);
        if (n % 2 == 0) {
            return half * half;
        } else {
            return half * half * x;
        }
    }
    double myPow(double x, int n) {
        long long N = n;
        if (N < 0) {
            x = 1 / x;
            N = -N;
        }
        return fastPow(x, N);
    }
};

//快速幂算法(循环)
class Solution {
public:
    double myPow(double x, int n) {
        long long N = n;
        if (N < 0) {
            x = 1 / x;
            N = -N;
        }
        double ans = 1;
        double current_product = x;
        for (long long i = N; i ; i /= 2) {
            if ((i % 2) == 1) {
                ans = ans * current_product;
            }
            current_product = current_product * current_product;
        }
        return ans;
    }
};