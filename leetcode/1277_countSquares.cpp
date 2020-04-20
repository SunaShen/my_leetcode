// @File   : 1277_countSquares.cpp
// @Source : https://leetcode-cn.com/problems/count-square-submatrices-with-all-ones/
// @Title  : 1277. 统计全为 1 的正方形子矩阵
// @Auther : sun_ds
// @Date   : 2020/3/19

/**  题目描述：
    给你一个 m * n 的矩阵，矩阵中的元素不是 0 就是 1，请你统计并返回其中完全由 1 组成的 正方形 子矩阵的个数。



    示例 1：

    输入：matrix =
    [
      [0,1,1,1],
      [1,1,1,1],
      [0,1,1,1]
    ]
    输出：15
    解释：
    边长为 1 的正方形有 10 个。
    边长为 2 的正方形有 4 个。
    边长为 3 的正方形有 1 个。
    正方形的总数 = 10 + 4 + 1 = 15.
    示例 2：

    输入：matrix =
    [
      [1,0,1],
      [1,1,0],
      [1,1,0]
    ]
    输出：7
    解释：
    边长为 1 的正方形有 6 个。
    边长为 2 的正方形有 1 个。
    正方形的总数 = 6 + 1 = 7.


    提示：

    1 <= arr.length <= 300
    1 <= arr[0].length <= 300
    0 <= arr[i][j] <= 1
*/


/**
 *
 * 1.dp
 * dp(m+1,vector<int>(n+1,0))
 * dp[i][j]表示，在左上角矩阵中由matrix[i-1][j-1]参与构成的最大正方形边长。
 * matrix[i-1][j-1]作为正方形的右下角的情况下，最大正方形边长。也可以说，matrix[i-1][j-1]左上角部分中，以matrix[i-1][j-1]参与构成的最大长方形边长。
 *
 * dp[i][j]的值表示以matrix[i-1][j-1]为右下角的正方形最大的边长。若dp[i][j] = 3;则，matrix[i-1][j-1]位置做右下角一定组成了1*1，2*2，3*3大小的矩形。
 * 即dpdp[i][j]既是matrix[i-1][j-1]为右下角的正方形最大的边长，又是matrix[i-1][j-1]为右下角组成的不同大小的正方形的个数。
 *
 * 有转移方程：
 * dp[i][j] = min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1])+1;
 * 当前位置，由其上、左、左上三个位置来更新。为三个位置最小值+1;
 *
 * 221. 最大正方形 的 改编版
 *
 * 使用res记录dp过程中的值。得到的值即为形成正方形的个数。
 *
 */

class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        if(matrix.size()==0||matrix[0].size()==0) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m+1,vector<int>(n+1,0));
        int res = 0;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(matrix[i-1][j-1]==1){
                    dp[i][j] = min(min(dp[i-1][j],dp[i][j-1]),dp[i-1][j-1])+1;
                }else{
                    dp[i][j] = 0;
                }
                res += dp[i][j];
            }
        }
        return res;
    }
};


