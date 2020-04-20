// @File   : 72_minDistance.cpp
// @Source : https://leetcode-cn.com/problems/edit-distance/
// @Title  : 72. 编辑距离
// @Auther : sun_ds
// @Date   : 2020/4/6

/**  题目描述：
    给你两个单词 word1 和 word2，请你计算出将 word1 转换成 word2 所使用的最少操作数 。

    你可以对一个单词进行如下三种操作：

    插入一个字符
    删除一个字符
    替换一个字符
     

    示例 1：

    输入：word1 = "horse", word2 = "ros"
    输出：3
    解释：
    horse -> rorse (将 'h' 替换为 'r')
    rorse -> rose (删除 'r')
    rose -> ros (删除 'e')
    示例 2：

    输入：word1 = "intention", word2 = "execution"
    输出：5
    解释：
    intention -> inention (删除 't')
    inention -> enention (将 'i' 替换为 'e')
    enention -> exention (将 'n' 替换为 'x')
    exention -> exection (将 'n' 替换为 'c')
    exection -> execution (插入 'u')

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/edit-distance
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.dp
 * dp[i][j]表示 word1[0，i-1]和word2[0,j-1]之间的最小编辑距离
 * 当j=0时，dp[i][0] = i。当i=0时，dp[0][j] = j。
 * 若word1[i-1]==word2[j-1] 则dp[i][j] = dp[i-1][j-1];
 * 若word1[i-1]!=word2[j-1]
 * 考虑三种方法：
 *  1.插入 dp[i][j] = dp[i][j-1] + 1;
 *  2.删除 dp[i][j] = dp[i-1][j] + 1;
 *  3.替换 dp[i][j] = dp[i-1][j-1] + 1;
 *
 *
 *
 */


class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(m+1,vector<int>(n+1,0));
        //初始条件很重要
        for(int i=0;i<=m;i++) dp[i][0] = i;
        for(int j=0;j<=n;j++) dp[0][j] = j;

        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                // 注意-1
                if(word1[i-1]==word2[j-1]){
                    dp[i][j] = dp[i-1][j-1];
                }else{
                    dp[i][j] = min(min(dp[i-1][j],dp[i][j-1]),dp[i-1][j-1])+1;
                }
            }
        }
        return dp[m][n];
    }
};

