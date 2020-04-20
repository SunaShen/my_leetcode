// @File   : 10_isMatch.cpp
// @Source : https://leetcode-cn.com/problems/regular-expression-matching/
// @Title  : 10. 正则表达式匹配
// @Auther : sun_ds
// @Date   : 2020/4/10

/**  题目描述：
    给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

    '.' 匹配任意单个字符
    '*' 匹配零个或多个前面的那一个元素
    所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。

    说明:

    s 可能为空，且只包含从 a-z 的小写字母。
    p 可能为空，且只包含从 a-z 的小写字母，以及字符 . 和 *。
    示例 1:

    输入:
    s = "aa"
    p = "a"
    输出: false
    解释: "a" 无法匹配 "aa" 整个字符串。
    示例 2:

    输入:
    s = "aa"
    p = "a*"
    输出: true
    解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。
    示例 3:

    输入:
    s = "ab"
    p = ".*"
    输出: true
    解释: ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
    示例 4:

    输入:
    s = "aab"
    p = "c*a*b"
    输出: true
    解释: 因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。
    示例 5:

    输入:
    s = "mississippi"
    p = "mis*is*p*."
    输出: false


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/regular-expression-matching
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *  https://leetcode-cn.com/problems/regular-expression-matching/solution/dong-tai-gui-hua-zui-xiang-xi-jie-da-you-jian-zhi-/
 * dp
 * 定义dp[i][j]:s前i个字符[0,i)是否能匹配p的前j个字符[0,j)，要明确一点，这里是左闭右开的，因此此时是在比较s[i-1]与p[i-1]；
 * 转移方程：
 * 1.s[i-1]==p[j-1] 匹配上了
 *  dp[i][j] = dp[i-1][j-1];
 * 2.s[i-1]!=p[j-1]
 *  2.1 p[j-1]=="." 任意匹配
 *      dp[i][j] = dp[i-1][j-1];
 *  2.2 p[j-1]=="*" 需要考虑前面，匹配零个或多个前面的元素
 *      2.2.1 s[i-1]!=p[j-2] 此时如果还想匹配，"*"只能起作用匹配零个。
 *          dp[i][j] = dp[i][j-2]; (相当于去掉p[j-1]和p[j-2]) 对i没有任何贡献
 *      2.2.2 s[i-1]!=p[j-2]||p[j-2]=="."
 *          可以让*代表0个字符或多个字符，如果p[j-2]为'.'就可以替换为s[i-1]的字符，所以可以看成一类情况
 *          2.2.2.1 "*"代表0个 例如：s:aab,p:aabb*
 *              dp[i][j] = dp[i][j-2]; (相当于去掉p[j-1]和p[j-2]) 对i没有任何贡献
 *          2.2.2.2 "*"代表1个 例如：s:aab,p:aab*
 *              dp[i][j] = dp[i][j-1]; (取1个字符，相当于去掉p[j-1]) 对i没有任何贡献
 *          2.2.2.3 "*"代表多个 例如：s：aabb,p：aab*
 *              dp[i][j] = dp[i-1][j]; (取多个字符) s后移一位，p不变(因为*还能起作用)
 *  2.3 else（j处就是个普通字符，dp[i][j]肯定不能匹配了）
 *      dp[i][j] = false;
 *
 * 初始条件：
 * 1.初始化dp[0][0] = true;
 *  以理解角度两个都是空的字符串肯定互相匹配
 *  以代码角度，当s="a",p="a"时，dp[1][1] = dp[0][0],因此必须dp[0][0]取true
 * 2.初始化第一行，即s长度为0的情况，dp[0][j]
 *  只有遇到"*"，并且采取替换零个字符的策略才有可能
 *  //p[j-1]为*可以把j-2和j-1处的字符删去，只有[0,j-3]也为true才可以让dp[0,j-1]为true。
 *  if(p.charAt(j-1)=='*'&&dp[0][j-2])
 * 3.字符串为空长度为0，只需要判断他们是否为空即可
 *
 * s和p可能为空。空的长度就是0，但是这些情况都已经判断过了，只需要判断是否为null即可
 *  if(p.size()==0&&s.size()==0)
 *        return true;
 *  if(s.size()==0||p.size()==0)
 *        return false;
 *
 *
 *
 * 类型合并：
 * 合并p[j-1]=="*"的情况，共两种。
 * 1.不论p[j-2]是否等于s[i-1]都可以删除掉j-1和j-2处字符：     两个零次合并了。
 *      dp[i][j] = dp[i][j]||dp[i][j-2];
 * 2.只有p[j-2]==s[i-1]或p[j-2]==‘.’才可以让*取1个或者多个字符：  替换一个和多个合并了
 *      if(p[j-2]==s[i-1]||p[j-2]=='.')
 *          dp[i][j] = dp[i-1][j]||dp[i][j-1];
 *
 *
 */

class Solution {
public:
    bool isMatch(string s, string p) {
        if(p.size()==0&&s.size()==0)
          return true;
        if(s.size()==0||p.size()==0)
            return false;

        int len1 = s.size();
        int len2 = p.size();
        vector<vector<bool>> dp(len1+1,vector<bool>(len2+1,false));
        dp[0][0] = true;
        for(int i=1;i<=len2;i++){
            if(p[i-1]=='*'&&dp[0][i-2]){
                dp[0][i] = true;
            }
        }
        for(int i=1;i<=len1;i++){
            for(int j=1;j<=len2;j++){
                if(s[i-1]==p[j-1]){
                    dp[i][j] = dp[i-1][j-1];
                }else{
                    if(p[j-1]=='.'){
                        dp[i][j] = dp[i-1][j-1];
                    }else if(p[j-1]=='*'){
                        if(j>=2){
                            if(p[j-2]==s[i-1]||p[j-2]=='.'){
                                dp[i][j] =  dp[i-1][j]||dp[i][j-1];
                            }
                            dp[i][j] = dp[i][j]||dp[i][j-2];
                        }
                    }else{
                        dp[i][j] = false;
                    }
                }
            }
        }
        return dp[len1][len2];
    }
};

