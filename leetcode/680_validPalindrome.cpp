// @File   : 680_validPalindrome.cpp
// @Source : https://leetcode-cn.com/problems/valid-palindrome-ii/
// @Title  : 680. 验证回文字符串 Ⅱ
// @Auther : sun_ds
// @Date   : 2020/5/19

/**  题目描述：
    给定一个非空字符串 s，最多删除一个字符。判断是否能成为回文字符串。

    示例 1:

    输入: "aba"
    输出: True
    示例 2:

    输入: "abca"
    输出: True
    解释: 你可以删除c字符。
    注意:

    字符串只包含从 a-z 的小写字母。字符串的最大长度是50000。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/valid-palindrome-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.双指针
 * 双指针向中间收缩。
 * 若左右对应的值相等，则继续。
 * 若不相等，由于有删除一个字符的余量，有两种情况。
 * 1）去掉左边的 此时字符串编程 l+1 -- r 之间，而且此时必须全部对应，没有可以不相等的余地了。
 * 2）去掉右边的 此时字符串编程 l -- r-1 之间，而且此时必须全部对应，没有可以不相等的余地了。
 * 这两种只要有一个满足即可。
 *
 */

class Solution {
public:
    bool is_Palindrome(string& s,int left,int right){
        int l = left,r = right;
        while(l<r){
            if(s[l++]!=s[r--]) return false;
        }
        return true;
    }
    bool validPalindrome(string s) {
        int l = 0, r = s.size()-1;
        while(l<r){
            if(s[l] == s[r]){
                l++;
                r--;
            }else{
                return is_Palindrome(s,l+1,r)||is_Palindrome(s,l,r-1);
            }
        }
        return true;
    }
};


