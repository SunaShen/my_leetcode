// @File   : 486_PredictTheWinner.cpp
// @Source : https://leetcode-cn.com/problems/predict-the-winner/
// @Title  : 486. 预测赢家
// @Auther : sun_ds
// @Date   : 2020/9/1

/**  题目描述：
    给定一个表示分数的非负整数数组。 玩家 1 从数组任意一端拿取一个分数，随后玩家 2 继续从剩余数组任意一端拿取分数，然后玩家 1 拿，…… 。每次一个玩家只能拿取一个分数，分数被拿取之后不再可取。直到没有剩余分数可取时游戏结束。最终获得分数总和最多的玩家获胜。

    给定一个表示分数的数组，预测玩家1是否会成为赢家。你可以假设每个玩家的玩法都会使他的分数最大化。

     

    示例 1：

    输入：[1, 5, 2]
    输出：False
    解释：一开始，玩家1可以从1和2中进行选择。
    如果他选择 2（或者 1 ），那么玩家 2 可以从 1（或者 2 ）和 5 中进行选择。如果玩家 2 选择了 5 ，那么玩家 1 则只剩下 1（或者 2 ）可选。
    所以，玩家 1 的最终分数为 1 + 2 = 3，而玩家 2 为 5 。
    因此，玩家 1 永远不会成为赢家，返回 False 。
    示例 2：

    输入：[1, 5, 233, 7]
    输出：True
    解释：玩家 1 一开始选择 1 。然后玩家 2 必须从 5 和 7 中进行选择。无论玩家 2 选择了哪个，玩家 1 都可以选择 233 。
         最终，玩家 1（234 分）比玩家 2（12 分）获得更多的分数，所以返回 True，表示玩家 1 可以成为赢家。
     

    提示：

    1 <= 给定的数组长度 <= 20.
    数组里所有分数都为非负数且不会大于 10000000 。
    如果最终两个玩家的分数相等，那么玩家 1 仍为赢家。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/predict-the-winner
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
 */


class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int length = nums.size();
        auto dp = vector<vector<int>> (length, vector<int>(length));
        for (int i = 0; i < length; i++) {
            dp[i][i] = nums[i];
        }

        // 遍历顺序 从下到上，从左到右。
        for (int i = length - 2; i >= 0; i--) {
            for (int j = i + 1; j < length; j++) {
                dp[i][j] = max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]);
            }
        }
        return dp[0][length - 1] >= 0;
    }
};

class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int length = nums.size();
        auto dp = vector<int> (length);
        for (int i = 0; i < length; i++) {
            dp[i] = nums[i];
        }
        for (int i = length - 2; i >= 0; i--) {
            for (int j = i + 1; j < length; j++) {
                dp[j] = max(nums[i] - dp[j], nums[j] - dp[j - 1]);
            }
        }
        return dp[length - 1] >= 0;
    }
};
