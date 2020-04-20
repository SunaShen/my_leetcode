// @File   : 409_longestPalindrome.cpp
// @Source : https://leetcode-cn.com/problems/longest-palindrome/
// @Title  : 409. 最长回文串
// @Auther : sun_ds
// @Date   : 2020/3/19

/**  题目描述：
    给定一个包含大写字母和小写字母的字符串，找到通过这些字母构造成的最长的回文串。

    在构造过程中，请注意区分大小写。比如 "Aa" 不能当做一个回文字符串。

    注意:
    假设字符串的长度不会超过 1010。

    示例 1:

    输入:
    "abccccdd"

    输出:
    7

    解释:
    我们可以构造的最长的回文串是"dccaccd", 它的长度是 7。
*/

/**
 *
 * 统计原字符串各字符个数
 *
 * 最大回文肯定是由偶数个字符+一个奇数字符组成
 * 所以，统计奇数字符个数
 * 若奇数字符个数大于0.则结果为n-count+1
 * 若奇数字符个数等于0.则结果为n，全是偶数
 *
 *
 *
 *
 */

class Solution {
public:
    int longestPalindrome(string s) {
        int n = s.size();
        vector<int> v(58,0); //58 = 26 + 6 + 26
        for(int i=0;i<n;i++) v[s[i] - 'A']++;
        int count = 0;
        for(int i=0;i<58;i++){
            if(v[i]%2) count++;
        }
        return count == 0 ? n : n - count + 1;
    }
};



