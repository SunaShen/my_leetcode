// @File   : 400_findNthDigit.cpp
// @Source : https://leetcode-cn.com/problems/nth-digit/
// @Title  : 400. 第N个数字
// @Auther : sun_ds
// @Date   : 2020/3/17

/**  题目描述：
    在无限的整数序列 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...中找到第 n 个数字。

    注意:
    n 是正数且在32为整形范围内 ( n < 231)。

    示例 1:

    输入:
    3

    输出:
    3
    示例 2:

    输入:
    11

    输出:
    0

    说明:
    第11个数字在序列 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... 里是0，它是10的一部分。


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/nth-digit
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 找规律
 * 个位数占9个
 * 十位数占90*2个
 * 百位数占900*3个
 * 首先循环判断当前n是几位数的第几个位置
 * 通过这个位置除以位数即为这个位置是第几个数，取余为这个数的第几位。
 * 最终得到结果
 *
 *
 *
 */

class Solution {
public:
    int findNthDigit(int n) {
        long end = 9,count = 1;
        while(end<n){
            n -= end;
            count++;
            end = 9*pow(10,count-1)*count;
        }
        int num = (n-1)/count + pow(10,count-1), offset = count - (n-1)%count;
        num /= pow(10,offset-1);
        return num%10;
    }
};

