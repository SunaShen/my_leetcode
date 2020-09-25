// @File   : 1143_longestCommonSubsequence.cpp
// @Source : https://leetcode-cn.com/problems/longest-common-subsequence/
// @Title  : 1143. 最长公共子序列
// @Auther : sun_ds
// @Date   : 2020/9/14

/**  题目描述：
    给定两个字符串 text1 和 text2，返回这两个字符串的最长公共子序列的长度。

    一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
    例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。两个字符串的「公共子序列」是这两个字符串所共同拥有的子序列。

    若这两个字符串没有公共子序列，则返回 0。

     

    示例 1:

    输入：text1 = "abcde", text2 = "ace"
    输出：3
    解释：最长公共子序列是 "ace"，它的长度为 3。
    示例 2:

    输入：text1 = "abc", text2 = "abc"
    输出：3
    解释：最长公共子序列是 "abc"，它的长度为 3。
    示例 3:

    输入：text1 = "abc", text2 = "def"
    输出：0
    解释：两个字符串没有公共子序列，返回 0。
     

    提示:

    1 <= text1.length <= 1000
    1 <= text2.length <= 1000
    输入的字符串只含有小写英文字符。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/longest-common-subsequence
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.dp
 * dp[i][j] 表示 text1[0...i-1] 和 text2[0...j-1] 之间最长公共子序列的长度。
 *
 * 初始条件：
 *  dp[0][0] = dp[0][j] = dp[i][0] = 0;
 *
 * 转移方程：
 *  text1[i-1] == text2[j-1]  dp[i][j] = dp[i-1][j-1] + 1; 相等，入选公共子序列
 *  text1[i-1] != text2[j-1]  dp[i][j] = max(dp[i-1][j], dp[i][j-1]); 不相等，没贡献，各自退一步，选个大的。
 *
 *
 * 最终结果：
 *  dp[m][n]
 *
 * 时间复杂度：O(MN)
 * 空间复杂度：O(MN)
 *
 */

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        int res = 0;
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i-1] == text2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                }else{
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return dp[m][n];
    }
};
