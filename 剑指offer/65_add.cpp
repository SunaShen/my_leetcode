// @File   : 65_add.cpp
// @Source : https://leetcode-cn.com/problems/bu-yong-jia-jian-cheng-chu-zuo-jia-fa-lcof/
// @Title  : 面试题65. 不用加减乘除做加法
// @Auther : sun_ds
// @Date   : 2020/4/10

/**  题目描述：
    写一个函数，求两个整数之和，要求在函数体内不得使用 “+”、“-”、“*”、“/” 四则运算符号。

     

    示例:

    输入: a = 1, b = 1
    输出: 2
     

    提示：

    a, b 均可能是负数或 0
    结果不会溢出 32 位整数

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/bu-yong-jia-jian-cheng-chu-zuo-jia-fa-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 使用位运算实现加法
 * c1 = a^b 无进位加法值
 * c2 = a&b c2中为1的为表示有进位。
 *
 * 所以下一轮是  进位+上一轮无进位加法值 = c2<<1 + c1
 * 知道进位为0，停止循环
 *
 * 注意负值的情况
 * 若c2为int，则当c2位负值时，不能进行左移。
 * 使用无符号int表示。
 *
 *
 *
 */

class Solution {
public:
    int add(int a, int b) {
        while(b!=0){
            int c1 = a^b;
            unsigned int c2 = a&b;
            //负数不能左移，转成无符号
            c2 <<= 1;
            a = c1,b = c2;
        }
        return a;
    }
};

