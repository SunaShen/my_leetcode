// @File   : 62_lastRemaining.cpp
// @Source : https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/
// @Title  : 面试题62. 圆圈中最后剩下的数字
// @Auther : sun_ds
// @Date   : 2020/3/30

/**  题目描述：
    0,1,,n-1这n个数字排成一个圆圈，从数字0开始，每次从这个圆圈里删除第m个数字。求出这个圆圈里剩下的最后一个数字。

    例如，0、1、2、3、4这5个数字组成一个圆圈，从数字0开始每次删除第3个数字，则删除的前4个数字依次是2、0、4、1，因此最后剩下的数字是3。

     

    示例 1：

    输入: n = 5, m = 3
    输出: 3
    示例 2：

    输入: n = 10, m = 17
    输出: 2
     

    限制：

    1 <= n <= 10^5
    1 <= m <= 10^6

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.约瑟夫环
 *  f(n,m)表示最后会剩下的位置。已知当前m,n情况下肯定是删掉第m%n个。
 *  则问题化为以m%n为起点的f(n-1,m)问题.但是f(n-1,m)返回的最后一个剩下的坐标是相对于起点m%n的。
 *  所以对于f(n,m)来说要将f(n-1,m)的结果加上m%n并取模
 *  即 f(n,m) = (m % n + f(n-1,m)) % n;
 *
 *  递归or迭代
 *
 */

//递归
class Solution {
public:
    int func(int n,int m){
        if(n==1) return 0;
        return (func(n-1,m) + m%n)%n;
    }
    int lastRemaining(int n, int m) {
        return func(n,m);
    }
};
//迭代
class Solution {
public:
    int lastRemaining(int n, int m) {
        int res = 0;
        for(int i=2;i<=n;i++){
            res = (res + m)%i;
        }
        return res;
    }
};

