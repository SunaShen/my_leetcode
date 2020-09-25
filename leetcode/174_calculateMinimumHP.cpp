// @File   : 174_calculateMinimumHP.cpp
// @Source : https://leetcode-cn.com/problems/dungeon-game/
// @Title  : 174. 地下城游戏
// @Auther : sun_ds
// @Date   : 2020/7/12

/**  题目描述：
    一些恶魔抓住了公主（P）并将她关在了地下城的右下角。地下城是由 M x N 个房间组成的二维网格。我们英勇的骑士（K）最初被安置在左上角的房间里，他必须穿过地下城并通过对抗恶魔来拯救公主。

    骑士的初始健康点数为一个正整数。如果他的健康点数在某一时刻降至 0 或以下，他会立即死亡。

    有些房间由恶魔守卫，因此骑士在进入这些房间时会失去健康点数（若房间里的值为负整数，则表示骑士将损失健康点数）；其他房间要么是空的（房间里的值为 0），要么包含增加骑士健康点数的魔法球（若房间里的值为正整数，则表示骑士将增加健康点数）。

    为了尽快到达公主，骑士决定每次只向右或向下移动一步。

     

    编写一个函数来计算确保骑士能够拯救到公主所需的最低初始健康点数。

    例如，考虑到如下布局的地下城，如果骑士遵循最佳路径 右 -> 右 -> 下 -> 下，则骑士的初始健康点数至少为 7。

    -2 (K)	-3	3
    -5	-10	1
    10	30	-5 (P)
     

    说明:

    骑士的健康点数没有上限。

    任何房间都可能对骑士的健康点数造成威胁，也可能增加骑士的健康点数，包括骑士进入的左上角房间以及公主被监禁的右下角房间。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/dungeon-game
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.dp
 * dp[i][j] 表示从 (i,j) 位置开始到右下角所需要的最少的健康点数。
 * 从右下向左上更新。
 *
 * 转移方程：
 * dp[i][j] = max(min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j], 1);
 * 每个位置由其下和右更新(倒着更新)。每次取 min，即最小需要的健康点数。
 * 并且要保证需要的健康点数不能为负数，即最小为 1.
 *
 * 初始值:
 *  dp[m-1][n-1] = max((1 - dungeon[m-1][n-1]),1);
 *  最右一列和最下一行只能从一个位置更新。
 *
 * 最终结果为dp[0][0]
 *
 * 时间复杂度 O(M*N)
 * 空间复杂度 O(M*N)
 *
 */

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();
        vector<vector<int>> dp(m,vector<int>(n));
        dp[m-1][n-1] = max(1 - dungeon[m-1][n-1], 1);
        for(int i=m-2;i>=0;i--){
            dp[i][n-1] = max(dp[i+1][n-1] - dungeon[i][n-1] , 1);
        }
        for(int j=n-2;j>=0;j--){
            dp[m-1][j] = max(dp[m-1][j+1] - dungeon[m-1][j] , 1);
        }

        for(int i=m-2;i>=0;i--){
            for(int j=n-2;j>=0;j--){
                dp[i][j] = max(min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j], 1);
            }
        }

        return dp[0][0];
    }
};
