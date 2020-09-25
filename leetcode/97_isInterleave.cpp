// @File   : 97_isInterleave.cpp
// @Source : https://leetcode-cn.com/problems/interleaving-string/
// @Title  : 97. 交错字符串
// @Auther : sun_ds
// @Date   : 2020/7/18

/**  题目描述：
    给定三个字符串 s1, s2, s3, 验证 s3 是否是由 s1 和 s2 交错组成的。

    示例 1:

    输入: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
    输出: true
    示例 2:

    输入: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
    输出: false

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/interleaving-string
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 1.递归
 *  使用，i1、i2、i3 分别表示 s1,s2,s3 的位置。
 *  若 s1[i1] == s3[i3] 或 s2[i2] == s3[i3]，继续递归。
 *  直到 i3 == s3.size().
 *
 * 2.dp
 * dp[i][j] 表示 s1 匹配到位置 i，s2 匹配到位置 j。此时 s3 一定匹配到 s3[i+j].
 * 判断 s1[i1] == s3[i3] && dp[i-1][j] 或者 s2[i2] == s3[i3] && dp[i][j-1] 是否成立。
 * 更新当前 dp[i][j]
 * 最终得到 dp[m][n] 即为结果。
 *
 */

// 递归 超时
class Solution {
public:
    bool func(string& s1, string& s2, string& s3,int i1,int i2,int i3){
        if(i3 == s3.size()){
            return true;
        }
        if(i1 < s1.size() && s1[i1] == s3[i3] && func(s1,s2,s3,i1+1,i2,i3+1)){
            return true;
        }
        if(i2 < s2.size() && s2[i2] == s3[i3] && func(s1,s2,s3,i1,i2+1,i3+1)){
            return true;
        }
        return false;
    }
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.size() + s2.size() != s3.size()) return false;
        return func(s1,s2,s3,0,0,0);
    }
};



class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
        if(n1 + n2 != n3) return false;
        vector<vector<bool>> dp(n1+1,vector<bool>(n2+1, false));
        dp[0][0] = true;
        for(int i=1;i<=n1;i++){
            if(s1[i-1] == s3[i-1]){
                dp[i][0] = true;
            }else{
                break;
            }
        }
        for(int j=1;j<=n2;j++){
            if(s2[j-1] == s3[j-1]){
                dp[0][j] = true;
            }else{
                break;
            }
        }

        for(int i=1;i<=n1;i++){
            for(int j=1;j<=n2;j++){
                dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1]) || (dp[i][j-1] && s2[j-1] == s3[i+j-1]);
            }
        }
        return dp[n1][n2];
    }
};

