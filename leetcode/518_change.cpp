// @File   : 518_change.cpp
// @Source : https://leetcode-cn.com/problems/coin-change-2/
// @Title  : 518. 零钱兑换 II
// @Auther : sun_ds
// @Date   : 2020/4/23

/**  题目描述：
    给定不同面额的硬币和一个总金额。写出函数来计算可以凑成总金额的硬币组合数。假设每一种面额的硬币有无限个。 

     

    示例 1:

    输入: amount = 5, coins = [1, 2, 5]
    输出: 4
    解释: 有四种方式可以凑成总金额:
    5=5
    5=2+2+1
    5=2+1+1+1
    5=1+1+1+1+1
    示例 2:

    输入: amount = 3, coins = [2]
    输出: 0
    解释: 只用面额2的硬币不能凑成总金额3。
    示例 3:

    输入: amount = 10, coins = [10]
    输出: 1
     

    注意:

    你可以假设：

    0 <= amount (总金额) <= 5000
    1 <= coin (硬币面额) <= 5000
    硬币种类不超过 500 种
    结果符合 32 位符号整数

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/coin-change-2
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.dp
 * 错误示范：
 *  dp[i]为组成总金额为i的组合数。
 *  for(int i=1;i<=amount;i++)
 *      for(auto coin:coins)
 *         dp[i] += dp[i-coin];
 *  这样会出现重复的情况。
 *  如i=6.正确结果是 6 = 5+1；6 = 1+1+1+1+1+1；两种。
 *  通过上述计算结果为，6 = 5+1；6 = 1+1+1+1+1+1；6 = 1+5；三种。
 *  原因是这里忽略了选取硬币的顺序。即，正确结果的硬币选取顺序是升序或者降序的。
 *
 * 将上面的问题分解，假设只有硬币1.此时遍历更新不会有问题。
 *  for(int i=1;i<=amount;i++)
 *      dp[i] += dp[i-coin];
 *
 * 所以可以将该问题看做是二维dp
 *  dp[i][j]，表示使用前i个硬币组成总金额为j的组合数。
 * 使用一层一层的更新。
 * 第一次只有一个硬币。
 * 第二次更新需要 为 前i个硬币组成j的组合数 = 前i-1个硬币组成j的个数 + 前i个硬币组成j-coins[i]的个数
 *  dp[i][j] = dp[i-1][j] + dp[i][j-coins[i]];
 * 这样依次更新，使得硬币变得有序，减少重复的问题。
 *
 *
 * 接着减少一个维度。
 * for(auto coin:coins)
 *    for(int i=coin;i<=amount;i++)
 *       dp[i] += dp[i-coin];
 *
 *
 *
 * 本题的核心是循环更新的顺序！！！！！
 *
 *
 *
 *
 */

class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<int> dp(amount+1,0);
        dp[0] = 1;
        for(auto coin:coins){
            for(int i=coin;i<=amount;i++){
                dp[i] = dp[i] + dp[i - coin];
            }
        }
        return dp[amount];
    }
};
