// @File   : 08.11_waysToChange.cpp
// @Source : https://leetcode-cn.com/problems/coin-lcci/
// @Title  : 面试题 08.11. 硬币
// @Auther : sun_ds
// @Date   : 2020/4/23

/**  题目描述：
    硬币。给定数量不限的硬币，币值为25分、10分、5分和1分，编写代码计算n分有几种表示法。(结果可能会很大，你需要将结果模上1000000007)

    示例1:

     输入: n = 5
     输出：2
     解释: 有两种方式可以凑成总金额:
    5=5
    5=1+1+1+1+1
    示例2:

     输入: n = 10
     输出：4
     解释: 有四种方式可以凑成总金额:
    10=10
    10=5+5
    10=5+1+1+1+1+1
    10=1+1+1+1+1+1+1+1+1+1
    说明：

    注意:

    你可以假设：

    0 <= n (总金额) <= 1000000

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/coin-lcci
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/



/**
 *
 * 1.dp
 * 错误示范：
 *  dp[i]为组成总金额为i的组合数。
 *  for(int i=1;i<=n;i++)
 *      for(auto coin:coins)
 *         dp[i] += dp[i-coin];
 *  这样会出现重复的情况。
 *  如i=6.正确结果是 6 = 5+1；6 = 1+1+1+1+1+1；两种。
 *  通过上述计算结果为，6 = 5+1；6 = 1+1+1+1+1+1；6 = 1+5；三种。
 *  原因是这里忽略了选取硬币的顺序。即，正确结果的硬币选取顺序是升序或者降序的。
 *
 * 将上面的问题分解，假设只有硬币1.此时遍历更新不会有问题。
 *  for(int i=1;i<=n;i++)
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
 *    for(int i=coin;i<=n;i++)
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
    int waysToChange(int n) {
        vector<int> dp(n+1,0);
        vector<int> coins = {1,5,10,25};
        dp[0] = 1;
        for(auto coin:coins){
            for(int i=coin;i<=n;i++){
                dp[i] = (dp[i] + dp[i - coin])%1000000007;
            }
        }
        return dp[n];
    }
};


