// @File   : 63_uniquePathsWithObstacles.cpp
// @Source : https://leetcode-cn.com/problems/unique-paths-ii/
// @Title  : 不同路径 II
// @Auther : sun_ds
// @Date   : 2019/12/10

/**  题目描述：
    一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。

    机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。

    现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？



    网格中的障碍物和空位置分别用 1 和 0 来表示。

    说明：m 和 n 的值均不超过 100。

    示例 1:

    输入:
    [
      [0,0,0],
      [0,1,0],
      [0,0,0]
    ]
    输出: 2
    解释:
    3x3 网格的正中间有一个障碍物。
    从左上角到右下角一共有 2 条不同的路径：
    1. 向右 -> 向右 -> 向下 -> 向下
    2. 向下 -> 向下 -> 向右 -> 向右

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/unique-paths-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 类似62_uniquePaths，加入了不能通过的障碍
 * 1.dp
 * if obstacle[i][j] == 1
 *  dp[i,j] = 0;
 * else
 *  dp[i,j] = dp[i-1][j] + dp[i][j-1];
 *
 * 需要处理边界。第一行第一列
 * 注意obstacle[0][0] == 1的情况，直接返回0
 *
 *
 *
 */

//dp二维数组
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        if(obstacleGrid.size()==0||obstacleGrid[0].size()==0) return 0;
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        if(obstacleGrid[0][0] == 1 || obstacleGrid[m-1][n-1] == 1) return 0;
        vector<vector<long long>> dp(m,vector<long long>(n,0));

        for(int i=1;i<m;++i){
            if(obstacleGrid[i][0]==1)
                break;
            dp[i][0] = 1;
        }
        for(int j=1;j<n;++j){
            if(obstacleGrid[0][j]==1)
                break;
            dp[0][j] = 1;
        }
        for(int i=1;i<m;++i){
            for(int j=1;j<n;++j){
                if(obstacleGrid[i][j]==1)
                    dp[i][j] = 0;
                else
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};




//dp一维数组
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        if(obstacleGrid.size()==0||obstacleGrid[0].size()==0) return 0;
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        if(obstacleGrid[0][0] == 1||obstacleGrid[m-1][n-1] == 1) return 0;
        vector<long long> dp(m,0);
        for(int i=0;i<m;++i){
            if(obstacleGrid[i][0]==1)
                break;
            dp[i] = 1;
        }
        for(int i=1;i<n;++i){
            if(obstacleGrid[0][i]==0 && dp[0] == 1)
                dp[0] = 1;
            else
                dp[0] = 0;
            for(int j=1;j<m;++j){
                if(obstacleGrid[j][i]==1)
                    dp[j] = 0;
                else
                    dp[j] = dp[j] + dp[j-1];
            }
        }
        return dp[m-1];
    }
};