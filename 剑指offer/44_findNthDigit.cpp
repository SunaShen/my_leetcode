// @File   : 44_findNthDigit.cpp
// @Source : https://leetcode-cn.com/problems/shu-zi-xu-lie-zhong-mou-yi-wei-de-shu-zi-lcof/
// @Title  : 面试题44. 数字序列中某一位的数字
// @Auther : sun_ds
// @Date   : 2020/3/17

/**  题目描述：
    数字以0123456789101112131415…的格式序列化到一个字符序列中。在这个序列中，第5位（从下标0开始计数）是5，第13位是1，第19位是4，等等。

    请写一个函数，求任意第n位对应的数字。

     

    示例 1：

    输入：n = 3
    输出：3
    示例 2：

    输入：n = 11
    输出：0
     

    限制：

    0 <= n < 2^31
    注意：本题与主站 400 题相同：https://leetcode-cn.com/problems/nth-digit/

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/shu-zi-xu-lie-zhong-mou-yi-wei-de-shu-zi-lcof
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



