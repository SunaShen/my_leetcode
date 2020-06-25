// @File   : 139_wordBreak.cpp
// @Source : https://leetcode-cn.com/problems/word-break/
// @Title  : 139. 单词拆分
// @Auther : sun_ds
// @Date   : 2020/6/25

/**  题目描述：
    给定一个非空字符串 s 和一个包含非空单词列表的字典 wordDict，判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。

    说明：

    拆分时可以重复使用字典中的单词。
    你可以假设字典中没有重复的单词。
    示例 1：

    输入: s = "leetcode", wordDict = ["leet", "code"]
    输出: true
    解释: 返回 true 因为 "leetcode" 可以被拆分成 "leet code"。
    示例 2：

    输入: s = "applepenapple", wordDict = ["apple", "pen"]
    输出: true
    解释: 返回 true 因为 "applepenapple" 可以被拆分成 "apple pen apple"。
         注意你可以重复使用字典中的单词。
    示例 3：

    输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
    输出: false


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/word-break
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. dp
 *  dp[i] 表示 s[0...i-1] 这个子字符串可以被单词列表的字典表示。
 *  初始条件 dp[0] = true;
 *  转移方程：
 *  将 s[0...i-1] 拆成两部分。包括 s[0...j-1]和 s[j...i-1]
 *  则 dp[i] = dp[j] && {s[j...i-1]是字典中单词}
 *
 *  判断 s[j...i-1] 是否是字典中单词。可以使用 hash 或者字典树。
 *  此处使用 hash。
 *  将各个单词存入 unordered_set s_string 中。
 *  其中 s[j...i-1] = s.substr(j,i-j)
 *  使用 s_string.count(s.substr(j,i-j)) ?= 0 来判断是否包含该单词。
 *  如果包含该单词，且 dp[j] == true;则 dp[i] = true;
 *
 *  优化。每次 j 不用从 0 开始。而使 j 从大到小枚举，如果此时 i-j 大于字典中最大单词的长度，则没必要搜索了。
 *
 *
 */


class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        unordered_set<string> s_string;
        for(auto i:wordDict) s_string.insert(i);
        vector<bool> dp(n+1,false);
        dp[0] = true;
        for(int i=1;i<=n;i++){
            for(int j=0;j<i;j++){
                if(dp[j] && (s_string.count(s.substr(j,i-j)) != 0)){
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }
};


class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        unordered_set<string> s_string;
        int max_len = 0;
        for(auto i:wordDict){
            max_len = max(max_len, (int)i.size());
            s_string.insert(i);
        }
        vector<bool> dp(n+1,false);
        dp[0] = true;
        for(int i=1;i<=n;i++){
            for(int j=i-1;j>=max(i-max_len, 0);j--){
                if(dp[j] && (s_string.count(s.substr(j,i-j)) != 0)){
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }
};




