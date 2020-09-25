// @File   : 877_stoneGame.cpp
// @Source : https://leetcode-cn.com/problems/stone-game/
// @Title  : 877. 石子游戏
// @Auther : sun_ds
// @Date   : 2020/9/24

/**  题目描述：
    亚历克斯和李用几堆石子在做游戏。偶数堆石子排成一行，每堆都有正整数颗石子 piles[i] 。

    游戏以谁手中的石子最多来决出胜负。石子的总数是奇数，所以没有平局。

    亚历克斯和李轮流进行，亚历克斯先开始。 每回合，玩家从行的开始或结束处取走整堆石头。 这种情况一直持续到没有更多的石子堆为止，此时手中石子最多的玩家获胜。

    假设亚历克斯和李都发挥出最佳水平，当亚历克斯赢得比赛时返回 true ，当李赢得比赛时返回 false 。

     

    示例：

    输入：[5,3,4,5]
    输出：true
    解释：
    亚历克斯先开始，只能拿前 5 颗或后 5 颗石子 。
    假设他取了前 5 颗，这一行就变成了 [3,4,5] 。
    如果李拿走前 3 颗，那么剩下的是 [4,5]，亚历克斯拿走后 5 颗赢得 10 分。
    如果李拿走后 5 颗，那么剩下的是 [3,4]，亚历克斯拿走后 4 颗赢得 9 分。
    这表明，取前 5 颗石子对亚历克斯来说是一个胜利的举动，所以我们返回 true 。
     

    提示：

    2 <= piles.length <= 500
    piles.length 是偶数。
    1 <= piles[i] <= 500
    sum(piles) 是奇数。


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/stone-game
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. dp
 *  dp[i][j] 表示当数组剩余部分为下标 i 到下标 j 时，当前玩家与另一玩家分数之差的最大值。 (当前玩家不一定是先手)
 *  i <= j，dp 数组才有意义，因此令 i > j 时，dp[i][j] = 0;
 *  1) 当 i == j 时，只剩一个数字，当前玩家只能拿当前数字，另一个玩家没得拿，所以 dp[i][i] = nums[i]
 *  2) 当 i < j 时，当前玩家可以从两端选取，即选择 nums[i] 或 nums[j], 然后另一玩家从剩下得区间中选择数字。
 *   dp 记录两个玩家分数之差，因此选择最大分差， dp[i][j] = max(nums[i] - dp[i+1][j], nums[j] - dp[i][j-1]);
 *
 *  最终判断 dp[0][n-1] 的值，如果 dp[0][n-1] >= 0, 则先手得分大于等于后手得分，则先手为赢家；否则，后手为赢家。
 *
 *  时间复杂度 O(N^2)
 *  空间复杂度 O(N^2)  使用滚动数组能降至 O(N)
 *
 * 2. 数学
 *  前提是 n 为偶数。
 *  假设有 n 堆石子，n 是偶数，则每堆石子的下标从 0 到 n−1。根据下标将 n 堆石子分成两组，每组有 n/2 堆石子，下标为偶数的石子堆属于第一组，下标为奇数的石子堆属于第二组。
 *  初始时，行的开始处的石子堆位于下标 0，属于第一组，行的结束处的石子堆位于下标 n−1，属于第二组，因此作为先手的 Alex 可以自由选择取走第一组的一堆石子或者第二组的一堆石子。
 *   如果 Alex 取走第一组的一堆石子，则剩下的部分在行的开始处和结束处的石子堆都属于第二组，因此 Lee 只能取走第二组的一堆石子。
 *   如果 Alex 取走第二组的一堆石子，则剩下的部分在行的开始处和结束处的石子堆都属于第一组，因此 Lee 只能取走第一组的一堆石子。
 *  无论 Lee 取走的是开始处还是结束处的一堆石子，剩下的部分在行的开始处和结束处的石子堆一定是属于不同组的，因此轮到 Alex 取走石子时，Alex 又可以在两组石子之间进行自由选择。
 *  根据上述分析可知，作为先手的 Alex 可以在第一次取走石子时就决定取走哪一组的石子，并全程取走同一组的石子。既然如此，Alex 是否有必胜策略？
 *  答案是肯定的。将石子分成两组之后，可以计算出每一组的石子数量，同时知道哪一组的石子数量更多。
 *  Alex 只要选择取走数量更多的一组石子即可。因此，Alex 总是可以赢得比赛。
 *
 *  作者：LeetCode-Solution
 *  链接：https://leetcode-cn.com/problems/stone-game/solution/shi-zi-you-xi-by-leetcode-solution/
 *  来源：力扣（LeetCode）
 *  著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 *
 */

class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int length = piles.size();
        auto dp = vector<vector<int>>(length, vector<int>(length));
        for (int i = 0; i < length; i++) {
            dp[i][i] = piles[i];
        }
        for (int i = length - 2; i >= 0; i--) {
            for (int j = i + 1; j < length; j++) {
                dp[i][j] = max(piles[i] - dp[i + 1][j], piles[j] - dp[i][j - 1]);
            }
        }
        return dp[0][length - 1] > 0;
    }
};

class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int length = piles.size();
        auto dp = vector<int>(length);
        for (int i = 0; i < length; i++) {
            dp[i] = piles[i];
        }
        for (int i = length - 2; i >= 0; i--) {
            for (int j = i + 1; j < length; j++) {
                dp[j] = max(piles[i] - dp[j], piles[j] - dp[j - 1]);
            }
        }
        return dp[length - 1] > 0;
    }
};

class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        return true;
    }
};
