// @File   : LCP19_minimumOperations.cpp
// @Source : https://leetcode-cn.com/problems/UlBDOe/
// @Title  : LCP 19. 秋叶收藏集
// @Auther : sun_ds
// @Date   : 2020/10/1

/**  题目描述：
    小扣出去秋游，途中收集了一些红叶和黄叶，他利用这些叶子初步整理了一份秋叶收藏集 leaves， 字符串 leaves 仅包含小写字符 r 和 y， 其中字符 r 表示一片红叶，字符 y 表示一片黄叶。
    出于美观整齐的考虑，小扣想要将收藏集中树叶的排列调整成「红、黄、红」三部分。每部分树叶数量可以不相等，但均需大于等于 1。每次调整操作，小扣可以将一片红叶替换成黄叶或者将一片黄叶替换成红叶。请问小扣最少需要多少次调整操作才能将秋叶收藏集调整完毕。

    示例 1：

    输入：leaves = "rrryyyrryyyrr"

    输出：2

    解释：调整两次，将中间的两片红叶替换成黄叶，得到 "rrryyyyyyyyrr"
    示例 2：

    输入：leaves = "ryr"

    输出：0

    解释：已符合要求，不需要额外操作
    提示：
    3 <= leaves.length <= 10^5
    leaves 中只包含字符 'r' 和字符 'y'

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/UlBDOe
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.dp
 *  dp[i][j] 来表示从第 0 片树叶到第 i 片树叶（[0, i]），并且第 i 片树叶处于状态 j 的时候总共需要的最小操作次数。
 *  j 一共分为0、1、2三种状态，0 表示黄色前面的红色，1 表示中间的黄色，2 表示黄色后面的红色。
 *
 *  转移方程：
 *   1) j == 0
 *    第 i 个位置相处于 0 状态(黄色前面的红色), 说明 i 位置必须放红色，且 i-1 位置必须为 0 状态(当前 i 为黄色左边的红色，那么前一个位置也必定属于第一部分红色左边的红色状态)。
 *    如果 i 位置已经是红色 dp[i][0] = dp[i-1][0];
 *    如果 i 位置不是红色，需要交换操作 dp[i][0] = dp[i-1][0] + 1;
 *    综上， dp[i][0] = dp[i-1][0] + isYellow(1);
 *
 *   2) j == 1
 *    第 i 个位置相处于 1 状态(中间的黄色), 说明 i 位置必须放黄色，此时 i-1 位置必须为 0 或 1 状态
 *    如果 i 位置已经是黄色 dp[i][1] = min(dp[i-1][0], dp[i-1][1]);
 *    如果 i 位置不是黄色，需要交换操作 dp[i][1] = min(dp[i-1][0], dp[i-1][1]) + 1;
 *    综上， dp[i][1] = min(dp[i-1][0], dp[i-1][1]) + isRed(1);
 *
 *   3) j == 2
 *    第 i 个位置相处于 2 状态(黄色后面的红色), 说明 i 位置必须放红色，此时 i-1 位置必须为 1 或 2 状态(不能为 0 状态因为这样 1 状态的树叶个数变成 0 了，不符合题意)
 *    如果 i 位置已经是红色 dp[i][2] = min(dp[i-1][1], dp[i-1][2]);
 *    如果 i 位置不是红色，需要交换操作 dp[i][2] = min(dp[i-1][1], dp[i-1][2]) + 1;
 *    综上， dp[i][2] = min(dp[i-1][1], dp[i-1][2]) + isYellow(1);
 *
 *  边界条件：
 *  i = 0 的情况下，前面没有树叶，j 只能是 0 状态。 且 dp[0][0] = isYellow(1);
 *  dp[0][1], dp[0][2], dp[1][2], 不满足每一个状态至少一个树叶的约束，全部设置为无效值 INT_MAX(因为本题求最小)
 *
 *  最终 dp[n-1][2] 即为最终结果
 *
 *
 *  时间复杂度 O(N)
 *  空间复杂度 O(N)
 *
 */

class Solution {
public:
    int minimumOperations(string leaves) {
        int n = leaves.size();
        vector<vector<int>> dp(n, vector<int>(3));
        dp[0][0] = (leaves[0] == 'y');
        dp[0][1] = dp[0][2] = dp[1][2] = INT_MAX;
        for (int i = 1; i < n; ++i) {
            int isRed = (leaves[i] == 'r');
            int isYellow = (leaves[i] == 'y');
            dp[i][0] = dp[i - 1][0] + isYellow;
            dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + isRed;
            if (i >= 2) {
                dp[i][2] = min(dp[i - 1][1], dp[i - 1][2]) + isYellow;
            }
        }
        return dp[n - 1][2];
    }
};
