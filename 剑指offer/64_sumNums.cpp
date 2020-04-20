// @File   : 64_sumNums.cpp
// @Source : https://leetcode-cn.com/problems/qiu-12n-lcof/
// @Title  : 面试题64. 求1+2+…+n
// @Auther : sun_ds
// @Date   : 2020/4/6

/**  题目描述：
    求 1+2+...+n ，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。

     

    示例 1：

    输入: n = 3
    输出: 6
    示例 2：

    输入: n = 9
    输出: 45
     

    限制：

    1 <= n <= 10000

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/qiu-12n-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 啥都不让用。
 * 不能乘法和除法。还好可以用加号。
 * 但是不能用循环。所以只能用递归加。
 * 但是递归需要条件判断结束条件。
 * 利用&&，短路与来充当if。强无敌。
 *
 * 加法替换乘法
 * 递归替换循环
 * 短路与替换判断
 *
 *
 */


class Solution {
public:
    int sumNums(int n) {
        n&&(n+=sumNums(n-1));
        return n;
    }
};


//写完才发现根本不行
class Solution {
public:
    int sumNums(int n) {
        //判断奇偶
        bool flag=false;
        if(n&1) flag = true;
        int k = n+1;
        int m = n>>1;
        int res = 0;
        if(flag) res+=m+1;
        int temp = k;
        while(m!=0){
            if(m&1) res += temp;
            temp <<= 1;
            m>>=1;
        }
        return res;
    }
};

