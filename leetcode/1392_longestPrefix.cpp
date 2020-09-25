// @File   : 1392_longestPrefix.cpp
// @Source : https://leetcode-cn.com/problems/longest-happy-prefix/
// @Title  : 1392. 最长快乐前缀
// @Auther : sun_ds
// @Date   : 2020/9/9

/**  题目描述：
    「快乐前缀」是在原字符串中既是 非空 前缀也是后缀（不包括原字符串自身）的字符串。

    给你一个字符串 s，请你返回它的 最长快乐前缀。

    如果不存在满足题意的前缀，则返回一个空字符串。

     

    示例 1：

    输入：s = "level"
    输出："l"
    解释：不包括 s 自己，一共有 4 个前缀（"l", "le", "lev", "leve"）和 4 个后缀（"l", "el", "vel", "evel"）。最长的既是前缀也是后缀的字符串是 "l" 。
    示例 2：

    输入：s = "ababab"
    输出："abab"
    解释："abab" 是最长的既是前缀也是后缀的字符串。题目允许前后缀在原字符串中重叠。
    示例 3：

    输入：s = "leetcodeleet"
    输出："leet"
    示例 4：

    输入：s = "a"
    输出：""
     

    提示：

    1 <= s.length <= 10^5
    s 只含有小写英文字母

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/longest-happy-prefix
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. Rabin-Karp 字符串编码
 *  遍历 s, 记录前缀和后缀对应的 Rabin-Karp 字符串编码值，编码值相等时表示字符串相等。
 *
 *  Rabin-Karp 使用 字符种类作为 base，将字符串按照 base 进制数解析，并转成 10 进制，取模(字符串太长)
 *  则该编码值可以看做是当前子串的一个哈希值。
 *
 *  其中 base 和 mod 都尽量选取质数，防止哈希冲突。
 *
 *  时间复杂度 O(N)
 *  空间复杂度 O(1)
 *
 * 2. KMP
 *  KMP 的 next 数组刚好满足题目要求。
 *  既是前缀也是后缀。
 *
 *  时间复杂度 O(N)
 *  空间复杂度 O(N)
 *
 */

class Solution {
public:
    string longestPrefix(string s) {
        int n = s.size();
        int prefix = 0, suffix = 0;
        int base = 31, mod = 1e9+7, mul = 1;
        int happy = 0;
        for (int i = 1; i < n; ++i) {
            prefix = ((long long)prefix * base + (s[i - 1] - 'a')) % mod;
            suffix = (suffix + (long long)(s[n - i] - 'a') * mul) % mod;
            if (prefix == suffix) {
                happy = i;
            }
            mul = (long long)mul * base % mod;
        }
        return s.substr(0, happy);
    }
};

class Solution {
public:
    string longestPrefix(string s) {
        int n = s.size();

        vector<int> next(n+1, 0);
        int i = 0, j = -1;
        next[0] = -1;
        while(i < n){
            while(j >= 0 && s[i] != s[j]) j = next[j];
            i++;
            j++;
            next[i] = j;
        }

        return s.substr(0, next[n]);
    }
};
