// @File   : 392_isSubsequence.cpp
// @Source : https://leetcode-cn.com/problems/is-subsequence/
// @Title  : 392. 判断子序列
// @Auther : sun_ds
// @Date   : 2020/7/27

/**  题目描述：
    给定字符串 s 和 t ，判断 s 是否为 t 的子序列。

    你可以认为 s 和 t 中仅包含英文小写字母。字符串 t 可能会很长（长度 ~= 500,000），而 s 是个短字符串（长度 <=100）。

    字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。（例如，"ace"是"abcde"的一个子序列，而"aec"不是）。

    示例 1:
    s = "abc", t = "ahbgdc"

    返回 true.

    示例 2:
    s = "axc", t = "ahbgdc"

    返回 false.

    后续挑战 :

    如果有大量输入的 S，称作S1, S2, ... , Sk 其中 k >= 10亿，你需要依次检查它们是否为 T 的子序列。在这种情况下，你会怎样改变代码？

    致谢:

    特别感谢 @pbrother 添加此问题并且创建所有测试用例。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/is-subsequence
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.双指针+贪心
 *  在 t 中找到 s 的各个字符。
 *  使得尽可能成功，则需要各个字符尽量靠前。
 *  因此，遍历 t，找到依次找 s 中的各个字符。(若有 t 中有多个位置都是对应的字符，选择最左边的肯定没错，且成功几率更大)
 *
 *  使用双指针分别指向 t 和 s。当遍历结束时，看指针是否指向 s 的结尾。
 *
 *  时间复杂度 O(M+N)
 *  空间复杂度 O(1)
 *
 * 2.dp
 *  dp[i][j] 表示在 t 中，从位置 i 开始，j 字符第一次出现的位置。
 *  若当前 t[i] == j, 则 dp[i][j] = i;
 *  若当前 t[i] != j, 则 j 字符出现在后面，使用 dp[i][j] = dp[i+1][j];
 *
 *  其中 i 的取值为 t 的长度，j 的取值为 26 个字符。
 *
 *  更新方式，从后往前。
 *
 *  初始条件。
 *  m = t.size()
 *  设置 dp[m][j] = m.其中 j = 1..26，=m 表示后面没有对应的 j 字符了。
 *
 *  构建好 dp。
 *  遍历 s 字符串。按照 dp 指引，依次跳转。
 *  若过程中出现下一个字符出现在 m 位置，则失败。
 *  否则，成功。
 *
 *  时间复杂度 O(M*26+N)
 *  空间复杂度 O(M*26)
 *
 *
 *
 */


class Solution {
public:
    bool isSubsequence(string s, string t) {
        int m = s.size(), n = t.size();
        int i=0, j=0;
        while(i < m && j < n){
            if (s[i] == t[j]) {
                i++;
            }
            j++;
        }
        return i == m;
    }
};

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int n = s.size(), m = t.size();

        vector<vector<int> > dp(m + 1, vector<int>(26, 0));
        //初始条件
        for (int i = 0; i < 26; i++) {
            dp[m][i] = m;
        }

        for (int i = m - 1; i >= 0; i--) {
            for (int j = 0; j < 26; j++) {
                if (t[i] == j + 'a')
                    dp[i][j] = i;
                else
                    dp[i][j] = dp[i + 1][j];
            }
        }
        int index = 0;
        for (int i = 0; i < n; i++) {
            if (dp[index][s[i] - 'a'] == m) {
                return false;
            }
            // 跳转
            index = dp[index][s[i] - 'a'] + 1;
        }
        return true;
    }
};

