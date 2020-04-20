// @File   : 231_isPowerOfTwo.cpp
// @Source : https://leetcode-cn.com/problems/power-of-two/
// @Title  : 231. 2的幂
// @Auther : sun_ds
// @Date   : 2020/3/26

/**  题目描述：
    给定一个整数，编写一个函数来判断它是否是 2 的幂次方。

    示例 1:

    输入: 1
    输出: true
    解释: 20 = 1
    示例 2:

    输入: 16
    输出: true
    解释: 24 = 16
    示例 3:

    输入: 218
    输出: false

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/power-of-two
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 1.移位
 *
 */


class Solution {
public:
    bool isPowerOfTwo(int n) {
        int temp = 1;
        for(int i=0;i<31;i++){
            if(n==temp)return true;
            temp <<= 1;
        }
        return false;
    }
};

