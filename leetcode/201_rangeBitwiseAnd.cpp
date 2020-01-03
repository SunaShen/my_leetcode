// @File   : 201_rangeBitwiseAnd.cpp
// @Source : https://leetcode-cn.com/problems/bitwise-and-of-numbers-range/solution/
// @Title  : 数字范围按位与
// @Auther : sun_ds
// @Date   : 2019/12/12

/**  题目描述：
    给定范围 [m, n]，其中 0 <= m <= n <= 2147483647，返回此范围内所有数字的按位与（包含 m, n 两端点）。

    示例 1: 

    输入: [5,7]
    输出: 4
    示例 2:

    输入: [0,1]
    输出: 0

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/bitwise-and-of-numbers-range
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 连续的数字做位与，连续数字的低位会有反转。因此，获得起点和终点的高位相同的部分，低位置零。
 *
 * 为什么找前缀就是答案？明确下面2个点：
 * 理论1：当一个二进制数+1时，一定存在某一位，这一位后面的数字，全部被置为相反数
 * 理论2：一旦某一位改变过(0->1或1->0)，这一位改变后和改变前相与结果肯定是0，那么一连串与下来更为0。之前的位与结果不变
 * 有上面两点的理论依据后，从m一直+1直到n的过程中，一定有很多位都改变过 分为2种情况
 * 1：存在一些高位没变过(为什么是高位，因为理论1)
 * 2：所有位都变过
 * 如果是情况1，改变位后面的结果全为0，前面的不变，所以最终结果就是 没改变的高位+后面一串0
 * 如果是情况2，所有位都改变过，所以最终结果为0
 * 作者：ant-8
 * 链接：https://leetcode-cn.com/problems/bitwise-and-of-numbers-range/solution/zheng-ming-wei-shi-yao-zhao-qian-zhui-jiu-shi-da-a/
 * 来源：力扣（LeetCode）
 * 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 *
 *
 */


class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int c = 0;
        while(m!=n){
            m>>=1;
            n>>=1;
            ++c;
        }
        return n<<c;
    }
};

class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        uint32_t p = 0xffffffff;

        while (m != n) {
            p <<= 1;
            m &= p;
            n &= p;
        }

        return m;
    }
};

//n逐渐减小。
//直到n<=m结束
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        while(n>m)
            n&=(n-1);
        return n;
    }
};