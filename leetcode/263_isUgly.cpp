// @File   : 263_isUgly.cpp
// @Source : https://leetcode-cn.com/problems/ugly-number/submissions/
// @Title  : 丑数
// @Auther : sun_ds
// @Date   : 2020/1/17

/**  题目描述：
    编写一个程序判断给定的数是否为丑数。

    丑数就是只包含质因数 2, 3, 5 的正整数。

    示例 1:

    输入: 6
    输出: true
    解释: 6 = 2 × 3
    示例 2:

    输入: 8
    输出: true
    解释: 8 = 2 × 2 × 2
    示例 3:

    输入: 14
    输出: false
    解释: 14 不是丑数，因为它包含了另外一个质因数 7。
    说明：

    1 是丑数。
    输入不会超过 32 位有符号整数的范围: [−2^31,  2^31 − 1]。


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/ugly-number
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 丑数：只包含质因子2，3和5的数
 *
 * 负数和0都不算丑数。1位丑数。
 * 使用while循环判断判断num是否能被2，3，5整除。如果不行，则return false。
 * 若能被这几个质因子整除，则继续循环，直到num = 1时，可以判断该数为丑数。
 *
 */

class Solution {
public:
    bool isUgly(int num) {
        if(num<=0) return false;
        while(num!=1){
            if(num%2 == 0) num/=2;
            else if(num%3 == 0) num/=3;
            else if(num%5 == 0) num/=5;
            else return false;
        }
        return true;
    }
};

