// @File   : 279_numSquares.cpp
// @Source : https://leetcode-cn.com/problems/perfect-squares/
// @Title  : 279. 完全平方数
// @Auther : sun_ds
// @Date   : 2020/4/21

/**  题目描述：
    给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。你需要让组成和的完全平方数的个数最少。

    示例 1:

    输入: n = 12
    输出: 3
    解释: 12 = 4 + 4 + 4.
    示例 2:

    输入: n = 13
    输出: 2
    解释: 13 = 4 + 9.

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/perfect-squares
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.dp
 * dp[i]表示数字i的完全平方数的最小个数
 * 初始化，各个本身就是完全平方数的，初始化为1
 * dp[i] = min(dp[i-j*j]+1)  j*j是完全平方数。遍历j即可得到dp[i]
 * 自下向上，得到dp[n]
 *
 */

class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n+1,INT_MAX);
        for(int i=1;i*i<=n;i++){
            dp[i*i] = 1;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j*j<i;j++){
                dp[i] = min(dp[i],dp[i-j*j]+1);
            }
        }
        return dp[n];
    }
};

