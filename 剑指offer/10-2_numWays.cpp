// @File   : 10-2_numWays.cpp
// @Source : https://leetcode-cn.com/problems/qing-wa-tiao-tai-jie-wen-ti-lcof/
// @Title  : 面试题10- II. 青蛙跳台阶问题
// @Auther : sun_ds
// @Date   : 2020/2/19

/**  题目描述：
    一只青蛙一次可以跳上1级台阶，也可以跳上2级台阶。求该青蛙跳上一个 n 级的台阶总共有多少种跳法。

    答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

    示例 1：

    输入：n = 2
    输出：2
    示例 2：

    输入：n = 7
    输出：21
    提示：

    0 <= n <= 100
    注意：本题与主站 509 题相同：https://leetcode-cn.com/problems/fibonacci-number/

     



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/qing-wa-tiao-tai-jie-wen-ti-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 类似斐波那契数
 * dp
 *
 */

class Solution {
public:
    int numWays(int n) {
        if(n == 0) return 1;
        if(n == 1) return 1;
        int pre1 = 1, pre2 = 1;
        long curr;
        for(int i=2;i<=n;i++){
            curr = (pre1 + pre2) % 1000000007;
            pre2 = pre1;
            pre1 = curr;
        }
        return (int)curr;
    }
};