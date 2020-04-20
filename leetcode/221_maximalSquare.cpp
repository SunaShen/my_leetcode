// @File   : 221_maximalSquare.cpp
// @Source : https://leetcode-cn.com/problems/maximal-square/
// @Title  : 221. 最大正方形
// @Auther : sun_ds
// @Date   : 2020/3/19

/**  题目描述：
    在一个由 0 和 1 组成的二维矩阵内，找到只包含 1 的最大正方形，并返回其面积。

    示例:

    输入:

    1 0 1 0 0
    1 0 1 1 1
    1 1 1 1 1
    1 0 0 1 0

    输出: 4

*/

/**
 *
 * 1.dp
 * dp(m+1,vector<int>(n+1,0))
 * dp[i][j]表示，在左上角矩阵中由matrix[i-1][j-1]参与构成的最大正方形边长。
 * matrix[i-1][j-1]作为正方形的右下角的情况下，最大正方形边长。也可以说，matrix[i-1][j-1]左上角部分中，以matrix[i-1][j-1]参与构成的最大长方形边长。
 *
 * 有转移方程：
 * dp[i][j] = min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1])+1;
 * 当前位置，由其上、左、左上三个位置来更新。为三个位置最小值+1;
 *
 * 遍历过程，从左上向右下。
 *
 * 使用res记录dp过程中的最大值。即为最大正方形边长。
 *
 *
 *
 */

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if(matrix.size()==0||matrix[0].size()==0)return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m+1,vector<int>(n+1,0));
        int res = 0;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(matrix[i-1][j-1]=='1'){
                    dp[i][j] = min(min(dp[i-1][j],dp[i][j-1]),dp[i-1][j-1])+1;
                    res = max(res,dp[i][j]);
                }
            }
        }
        return res*res;
    }
};

//使用一维dp
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if(matrix.size()==0||matrix[0].size()==0)return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<int> dp(n+1,0);
        int res = 0;
        for(int i=1;i<=m;i++){
            int pre = 0;
            for(int j=1;j<=n;j++){
                int temp = dp[j];
                if(matrix[i-1][j-1]=='1'){
                    //pre代表左上，dp[j]代表上，dp[j-1]代表左
                    dp[j] = min(min(dp[j],pre),dp[j-1])+1;
                    res = max(res,dp[j]);
                }else{
                    dp[j] = 0;
                }
                pre = temp;
            }
        }
        return res*res;
    }
};


