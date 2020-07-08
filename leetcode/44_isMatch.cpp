// @File   : 44_isMatch.cpp
// @Source : https://leetcode-cn.com/problems/wildcard-matching/
// @Title  : 44. 通配符匹配
// @Auther : sun_ds
// @Date   : 2020/7/5

/**  题目描述：
    给定一个字符串 (s) 和一个字符模式 (p) ，实现一个支持 '?' 和 '*' 的通配符匹配。

    '?' 可以匹配任何单个字符。
    '*' 可以匹配任意字符串（包括空字符串）。
    两个字符串完全匹配才算匹配成功。

    说明:

    s 可能为空，且只包含从 a-z 的小写字母。
    p 可能为空，且只包含从 a-z 的小写字母，以及字符 ? 和 *。
    示例 1:

    输入:
    s = "aa"
    p = "a"
    输出: false
    解释: "a" 无法匹配 "aa" 整个字符串。
    示例 2:

    输入:
    s = "aa"
    p = "*"
    输出: true
    解释: '*' 可以匹配任意字符串。
    示例 3:

    输入:
    s = "cb"
    p = "?a"
    输出: false
    解释: '?' 可以匹配 'c', 但第二个 'a' 无法匹配 'b'。
    示例 4:

    输入:
    s = "adceb"
    p = "*a*b"
    输出: true
    解释: 第一个 '*' 可以匹配空字符串, 第二个 '*' 可以匹配字符串 "dce".
    示例 5:

    输入:
    s = "acdcb"
    p = "a*c?b"
    输出: false

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/wildcard-matching
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 1.dp
 *  bool 类型的 dp[i][j] 表示 s[0:i-1] 与 p[0:j-1] 是否匹配。
 *  起始条件：
 *  当 i=0,j=0时，当做匹配。
 *  当 i=0时，只有当 j 为'*'才为 true；
 *  转移方程：
 *  当 s[i-1] == p[j-1] 时，dp[i][j] = dp[i-1][j-1].
 *  当 p[j-1] == '?' 时，可以对应成任何一个字符，dp[i][j] = dp[i-1][j-1].
 *  否则，当 p[j-1] == '*',可以当做空或者任意长度字符串。
 *      '*'当做空时，直接假装'*'不存在，只看 j-1 ，dp[i][j] = dp[i][j-1]
 *      '*'当做任意长度字符串时，表示这个'*'可以无限使用。所以 j 是不变的。i 在变。即 dp[i][j] = dp[i-1][j]
 *  最终得到 dp[m][n] 即为最终结果
 */

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();
        vector<vector<bool>> dp(m+1,vector<bool>(n+1,false));
        dp[0][0] = true;
        for(int i=1;i<=n;i++){
            if(p[i-1] != '*'){
                break;
            }
            dp[0][i] = true;
        }
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(s[i-1] == p[j-1] || p[j-1] == '?'){
                    dp[i][j] = dp[i-1][j-1];
                }else if(p[j-1] == '*'){
                    dp[i][j] = dp[i-1][j] || dp[i][j-1];
                }
            }
        }
        return dp[m][n];
    }
};

