// @File   : 367_isPerfectSquare.cpp
// @Source : https://leetcode-cn.com/problems/valid-perfect-square/
// @Title  : 367. 有效的完全平方数
// @Auther : sun_ds
// @Date   : 2020/3/30

/**  题目描述：
    给定一个正整数 num，编写一个函数，如果 num 是一个完全平方数，则返回 True，否则返回 False。

    说明：不要使用任何内置的库函数，如  sqrt。

    示例 1：

    输入：16
    输出：True
    示例 2：

    输入：14
    输出：False

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/valid-perfect-square
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 二分法 从 0 ~ num/2
 *
 */


class Solution {
public:
    bool isPerfectSquare(int num) {
        if(num<2) return true;
        int l=0,r=num/2;
        while(l<=r){
            //防止 mid*mid溢出
            long long mid =  l + ((r - l)>>1);
            if(mid*mid==num){
                return true;
            }else if(mid*mid<num){
                l = mid + 1;
            }else{
                r = mid - 1;
            }
        }
        return false;
    }
};

